#include "entrypoint.h"
#include "raylib.h"

#include <stdio.h>
#include <time.h>

void CustomLog(int msgType, const char *text, va_list args){ 
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", timeStr);

    switch (msgType)
    {
        case LOG_INFO: printf("[INFO] : "); break;
        case LOG_ERROR: printf("[ERROR]: "); break;
        case LOG_WARNING: printf("[WARN] : "); break;
        case LOG_DEBUG: printf("[DEBUG]: "); break;
        default: break;
    }

    vprintf(text, args);
    printf("\n");
}

void raylib_start(void){
    SetTraceLogCallback(CustomLog);
    InitWindow(640,480,"Labo: Services");
    TraceLog(LOG_INFO,"Window opened; width: %d height: %d",640,480);
    TraceLog(LOG_INFO,"Engine intiliazed successfully");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        static float pos[4] = {0,0,100,100};
        float dt = GetFrameTime();

        if(IsKeyDown(KEY_A)){
            pos[0] -= 100 *dt;
            TraceLog(LOG_ERROR,"Clicking A");
        }
        if(IsKeyDown(KEY_D)){
            pos[0] += 100 *dt;
            TraceLog(LOG_WARNING,"Clicking D");
        }
        if(IsKeyDown(KEY_W)){
            pos[1] -= 100 *dt;
            TraceLog(LOG_INFO,"Going up: Weeeeeeeeeeeeee");
        }
        if(IsKeyDown(KEY_S)){
            pos[1] += 100 *dt;
            TraceLog(LOG_INFO,"Stay down....");
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(pos[0],pos[1],pos[2],pos[3],RED);
        EndDrawing();
    }
}