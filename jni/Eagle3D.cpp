#ifdef _Android_
/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <jni.h>
#include <errno.h>
#include <EGL/egl.h>
#include <android/sensor.h>
#include <android_native_app_glue.h>
#include "Core.h"
#include "EagleLog.h"
#include <android/native_window.h>
#include "Window.h"


#include "SDL.h"
#include "SDL_log.h"
#include "SDL_main.h"


/**
 * Our saved state data.
 */
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

Core *core;
struct engine* engine;
static ANativeActivity* activity;
/**
 * Shared state for our app.
 */
struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};

static void OnApplicationQuit(){
	core->OnApplicationQuit();

	delete core;
	delete activity;
	delete engine;
}

static void Stop(){

	core->Stop();
}
static void Resume(){

	core->Resume();
}
static void Pause(){

	core->Pause();
}
static void LowMemory(){

	core->LowMemory();
}
//Destroy the current surface programs
static void OnSurfaceDestroy(){
	core->OnSurfaceDestroy();
}


//Create the whole programs
static void OnCreate(){

	activity=engine->app->activity;
	Core::SetActivity(activity);
	core=new Core();
	core->Start();

}

static void Resize(int32_t width,int32_t height){

	core->Resize(width,height);

}
/**
 * Initialize an EGL context for the current display.
 */
static int engine_init_display(struct engine* engine) {
    // initialize OpenGL ES and EGL
    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */

    const EGLint attribs[] = {

            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
    EGLint contextAttrs[] = {
         EGL_CONTEXT_CLIENT_VERSION, 2,
         EGL_NONE
    };

    context = eglCreateContext(display, config, NULL, contextAttrs);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;
    engine->state.angle = 0;

    return 0;
}

/**
 * Just the current frame in the display.
 */
static void engine_draw_frame(struct engine* engine) {

	if (engine->display == NULL) {
        // No display.
        return;
    }

    core->Render();
    eglSwapBuffers(engine->display, engine->surface);
}

/**
 * Tear down the EGL context currently associated with the display.
 */
static void engine_term_display(struct engine* engine) {

    if (engine->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (engine->context != EGL_NO_CONTEXT) {
            eglDestroyContext(engine->display, engine->context);
        }
        if (engine->surface != EGL_NO_SURFACE) {
            eglDestroySurface(engine->display, engine->surface);
        }
        eglTerminate(engine->display);
    }
    engine->animating = 0;
    engine->display = EGL_NO_DISPLAY;
    engine->context = EGL_NO_CONTEXT;
    engine->surface = EGL_NO_SURFACE;
}

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {

	struct engine* engine = (struct engine*)app->userData;
    int32_t eventType=AInputEvent_getType(event);
    switch(eventType){
    	case AINPUT_EVENT_TYPE_KEY:

            break;
    	case AINPUT_EVENT_TYPE_MOTION:
    		switch(AInputEvent_getSource(event)){
    		case AINPUT_SOURCE_TOUCHSCREEN:
    			switch(AMotionEvent_getAction(event)){
    				case AMOTION_EVENT_ACTION_MOVE:
    					//for(int i=0;i<AMotionEvent_getPointerCount(event);i++){
    					//	Input.SetMoveEventAction(AMotionEvent_getX(event,i),AMotionEvent_getY(event,i));
    					//}
    					break;
    				case AMOTION_EVENT_ACTION_DOWN:
    					//Input.SetDownEventAction(AMotionEvent_getX(event,i),AMotionEvent_getY(event,i));
    					break;
    				case AMOTION_EVENT_ACTION_UP:
    					//Input.SetUpEventAction(AMotionEvent_getX(event,i),AMotionEvent_getY(event,i));
    					break;
    			}
    			break;
    		case AINPUT_SOURCE_TRACKBALL:
    			break;
    		}
    		break;

    }

//    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
//        engine->animating = 1;
//        engine->state.x = AMotionEvent_getX(event, 0);
//        engine->state.y = AMotionEvent_getY(event, 0);
//        return 1;
//    }
    return 0;
}

static void Init_SDL_MAIN(){

		    SDL_SetMainReady();

		    /* Run the application code! */
		    int status;
		    char *argv[2];
		    argv[0] = SDL_strdup("SDL_app");
//		    char *buf = new char[strlen(filename)+1];
//		    strcpy(buf, filename);
//		    argv[1] = buf;
		    status = SDL_main(1, argv);

}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {

	engine = (struct engine*)app->userData;
    switch (cmd) {
    	case APP_CMD_START:

    		break;
    	case APP_CMD_DESTROY:
    		if(core!=NULL){
    		OnApplicationQuit();
    		}
    		break;
    	//内存不足
    	case APP_CMD_LOW_MEMORY:
    		if(core!=NULL){
    		LowMemory();
    		}
    		break;
    	case APP_CMD_PAUSE:
    		if(core!=NULL){
    		Pause();
    		}
    		break;
    	case APP_CMD_STOP:
    		if(core!=NULL){
    		Stop();
    		}
    		break;
    	//继续执行
    	case APP_CMD_RESUME:
    		if(core!=NULL){
    			//Resume();
    		}
    		break;
    	case APP_CMD_WINDOW_RESIZED:
    		Resize(ANativeWindow_getWidth(app->window),ANativeWindow_getHeight(app->window));
    		break;
        case APP_CMD_SAVE_STATE:

            // The system has asked us to save our current state.  Do so.
            engine->app->savedState = malloc(sizeof(struct saved_state));
            *((struct saved_state*)engine->app->savedState) = engine->state;
            engine->app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
        	if (engine->app->window != NULL) {
        	   Window::InitWindowSize(ANativeWindow_getWidth(app->window),ANativeWindow_getHeight(app->window));
        	   engine_init_display(engine);

        	   if(core==NULL){

        		   OnCreate();
        		//   Init_SDL_MAIN();
        	   }else{

        		   Resume();
        	   }
        	   engine_draw_frame(engine);
        	  }
            break;
        case APP_CMD_TERM_WINDOW:

        	OnSurfaceDestroy();
            // The window is being hidden or closed, clean it up.
            engine_term_display(engine);

            break;
        case APP_CMD_GAINED_FOCUS:
        	 // When our app gains focus, we start monitoring the accelerometer.
        	  if (engine->accelerometerSensor != NULL) {
        	    ASensorEventQueue_enableSensor(engine->sensorEventQueue,
        	         engine->accelerometerSensor);
        	  // We'd like to get 60 events per second (in us).
        	   ASensorEventQueue_setEventRate(engine->sensorEventQueue,
        	         engine->accelerometerSensor, (1000L/60)*1000);
        	 }
        	if(core==NULL){
        		return;
        	}
        	core->GetFocus();
            break;
        case APP_CMD_LOST_FOCUS:

            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
            if (engine->accelerometerSensor != NULL) {
                ASensorEventQueue_disableSensor(engine->sensorEventQueue,
                        engine->accelerometerSensor);
            }
            if(core==NULL){
                  return;
             }
            core->LoseFocus();
            // Also stop animating.
            //engine->animating = 0;
            //engine_draw_frame(engine);
            break;
    }
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) {
	app_dummy();
    struct engine engine;
    LOGI("Eagle3D Start");
    // Make sure glue isn't stripped.
    //app_dummy();

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;

    engine.app = state;

    // Prepare to monitor accelerometer
    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
            ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
            state->looper, LOOPER_ID_USER, NULL, NULL);

    if (state->savedState != NULL) {
        // We are starting with a previous saved state; restore from it.
        engine.state = *(struct saved_state*)state->savedState;
    }

    // loop waiting for stuff to do.

    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
                (void**)&source)) >= 0) {

            // Process this event.
            if (source != NULL) {
                source->process(state, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {
                if (engine.accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
                            &event, 1) > 0) {
                        //LOGI("accelerometer: x=%f y=%f z=%f",
                         //       event.acceleration.x, event.acceleration.y,
                         //       event.acceleration.z);
                    }
                }
            }

            // Check if we are exiting.
            if (state->destroyRequested != 0) {

            	OnSurfaceDestroy();
                engine_term_display(&engine);
                return;
            }

            engine_draw_frame(&engine);
        }


    }
}

int main(int argc, char *argv[]) {


   LOGI("SDL Main Start");
   return 1;
}
//END_INCLUDE(all)
#endif
