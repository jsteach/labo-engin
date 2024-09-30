#include "entrypoint.h"
#define SUPPORT_FILEFORMAT_MP3
#include "raylib.h"

#include <stdio.h>
#include <time.h>

#ifdef NDEBUG_MODE
static FILE* file_log = NULL;
#endif
void CustomLog(int msgType, const char *text, va_list args){ 
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    FILE* out = NULL;
    #ifdef NDEBUG_MODE
    out = file_log;
    #else
    out = stdout;
    #endif
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(out,"[%s] ", timeStr);

    switch (msgType)
    {
        case LOG_INFO:    fprintf(out,"[INFO] : "); break;
        case LOG_ERROR:   fprintf(out,"[ERROR]: "); break;
        case LOG_WARNING: fprintf(out,"[WARN] : "); break;
        case LOG_DEBUG:   fprintf(out,"[DEBUG]: "); break;
        default: break;
    }

    vfprintf(out,text, args);
    fprintf(out,"\n");
}

void raylib_start(void){
    #ifdef NDEBUG_MODE
    file_log = fopen("game_logs.txt","wb");
    if(file_log == NULL){
        printf("[ERROR]: Couldn't create log file...");
    }
    #endif
    SetTraceLogCallback(CustomLog);
    InitWindow(640,480,"Labo: Services");
    InitAudioDevice(); 
    SetTargetFPS(60);
    Music m = LoadMusicStream("assets/music.mp3");
    Texture tex = LoadTexture("assets/image.png");
    Sound snd = LoadSound("assets/soundfx.mp3");
    PlayMusicStream(m);
    while(!WindowShouldClose()){
        static float pos[4] = {0,0,100,100};
        float dt = GetFrameTime();

        UpdateMusicStream(m); 

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
        if(IsKeyDown(KEY_SPACE)){
            PlaySound(snd);
        }

        BeginDrawing();
        ClearBackground(BLACK);
        Rectangle src = {0,0,(float)tex.width,(float)tex.height};
        Rectangle dst = {pos[0],pos[1],100,100};
        DrawTexturePro(tex,src,dst,CLITERAL(Vector2){0},0,WHITE);
        DrawText("Press space for sound fx !",0,0,24,RED);
        EndDrawing();
    }
    #ifdef NDEBUG_MODE
    fclose(file_log);
    #endif
}