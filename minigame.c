#include "migame.h"

int cx,cy,x,y,ex,ey,ox,oy,score,prad,erad,orad;

void setValues()
{
    ex = rand() % 64 * 10;
    ey = rand() % 48 * 10;
    ox = rand() % 64 * 10;
    oy = rand() % 48 * 10;
}

int main(void)
{
    InitWindow(640, 480, "Mini Game");
    SetTargetFPS(60);
    srand(time(0));
    InitAudioDevice();
    Sound scoreless = LoadSound("score-.ogg");
    Texture2D playertexture = LoadTexture("omni chaen.PNG");
    cx = 320;
    cy = 240;
    x = cx;
    y = cy;
    score = 0;
    setValues();

    Vector2 player = {x,y};
    prad = 10;

    Vector2 enemy = {ex,ey};
    erad = 5;

    Vector2 obstacle = {ox,oy};
    orad = 6;

    double messageTimer = 0;
    const char* message = NULL;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        DrawText(TextFormat("score: %d",score),10,10,40,BLACK);
        DrawTexture(playertexture,player.x - playertexture.width/2,player.y - playertexture.height/2,WHITE);

        if(player.x<10) player.x=GetScreenWidth()-10;
        if(player.x>GetScreenWidth()) player.x=10;
        if(player.y<10) player.y=GetScreenHeight()-10;
        if(player.y>GetScreenHeight()) player.y=10;

        DrawCircleV(player,prad,BLANK);
        DrawCircleV(enemy,erad,RED);
        DrawCircleV(obstacle,orad,BLACK);

        if(messageTimer<=0)
        {
            if(IsKeyDown(KEY_W)) player.y-=5;
            if(IsKeyDown(KEY_A)) player.x-=5;
            if(IsKeyDown(KEY_S)) player.y+=5;
            if(IsKeyDown(KEY_D)) player.x+=5;
            if(IsKeyDown(KEY_C)){
                player.x=cx;
                player.y=cy;
            }
        }

        if (messageTimer > 0) {
            DrawText(message, 200, 240, 40, BLACK);
            messageTimer -= GetFrameTime();
        }        

        if(CheckCollisionCircles(player,prad+5,enemy,erad))
        {
            score++;
            setValues();
            enemy.x = ex;
            enemy.y = ey;
            obstacle.x = ox;
            obstacle.y = oy;

            message = "Score +";
            messageTimer = 1;  // show for 1 second

        }
        if(CheckCollisionCircles(player,prad+6,obstacle,orad))
        {
            if(score>=0)
            {
                score--;
            }
            setValues();
            enemy.x = ex;
            enemy.y = ey;
            obstacle.x = ox;
            obstacle.y = oy;

            PlaySound(scoreless);

            message = "Score -";
            messageTimer = 1;
        }

        if(score==8)
        {
            double pauseStart = GetTime();
            while(GetTime() - pauseStart < 1)
            {
                BeginDrawing();
                ClearBackground(WHITE);
                DrawText("Level Cleared",200,240,40,BLACK);
                EndDrawing();
            }
            break;
        }

        

        EndDrawing();
    }

    UnloadTexture(playertexture);
    CloseWindow();
    return 0;
}
