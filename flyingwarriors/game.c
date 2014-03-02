#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>
#include <SDL_mixer/SDL_mixer.h>
#include <time.h>
#define MAX_PONTS 100000

const int WIDTH = 800; //960
const int HEIGHT = 600; //557
const int BPP = 32;
//const int FRAMES_PER_SECOND = 20;

float vel_crobat = 1.75;
int upup = 1;
int leftleft = 1;
int rightright = 1;

int ast2 = 0;
int asteroid = 0;
int collision_on = 0;

int pont = 0;
char ponts[MAX_PONTS];
int all_enemies = 28;

#define NUMSPRITES 8

SDL_Surface* intro = NULL;
SDL_Surface* icon = NULL;
TTF_Font* fonte = NULL;
TTF_Font* pontos = NULL;
SDL_Surface* hero = NULL;
SDL_Surface* enemy1right = NULL;
SDL_Surface* enemy1left = NULL;
SDL_Surface* enemy2right = NULL;
SDL_Surface* enemy2left = NULL;
SDL_Surface* enemy3 = NULL;
SDL_Surface* enemy3left = NULL;
SDL_Surface* movebullet = NULL;
SDL_Surface* background = NULL;
SDL_Surface* screen = NULL;
Mix_Chunk* effect;
Mix_Music* fase1;

#define LASTFRAME 371


SDL_Event event;

int gamerunning = 1;

typedef struct _ASTEROIDE1
{

  int width;
  int height;
  int active;
  float sx;
  float sy;
  float dx;
  float dy;

}ZUBAT;

typedef struct _ASTEROIDE2
{

  int width;
  int height;
  int active;
  float sx;
  float sy;
  float dx;
  float dy;
  ZUBAT zubat[2];

}GOLBAT;

typedef struct _ASTEROIDE3
{

  int width;
  int height;
  int active;
  float sx;
  float sy;
  float dx;
  float dy;
  GOLBAT golbat[2];

}PLAYER;


PLAYER player, bullet;
PLAYER crobat[4];


     int direction = 0;
     float vel = 0;
     float vel_tiro = 30;
     int qnt_crobats = 0;
     int qnt_golbats = 0;
     int qnt_zubats = 0;
     int asteroid_level[4];
     int contador_tiro = 0, solta = 0, tiro = 0, change = 0;
     int quantiro = 0;
     int cont;



void LOAD_FILES()
{
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 );
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);
    icon = SDL_LoadBMP("ball.bmp");
    intro = IMG_Load("intro.jpg");
    fonte = TTF_OpenFont("pokemonhollow.ttf", 26);
    pontos = fonte;
    movebullet = IMG_Load("moltresbullet.png");
    fase1 = Mix_LoadMUS("break.mp3");
    hero = IMG_Load("latiassheet.png");
    enemy1right = IMG_Load("zubatright.png");
    enemy1left = IMG_Load("zubatleft.png");
    enemy2left = IMG_Load("golbatleft.png");
    enemy2right = IMG_Load("golbat.png");
    enemy3 = IMG_Load("crobatsheet.png");
    enemy3left = IMG_Load("crobatleft.png");
    //top = IMG_Load("top.jpg");
    background = IMG_Load("pokemonuniverse.jpg");

}

void PLAYER_INFO()
{
    player.width = 53;
    player.height = 53;
    player.dx = WIDTH/2;
    player.dy = HEIGHT/2;
    player.sx = 0;
    player.sy = 0;

    bullet.width = 53;
    bullet.height = 53;
    bullet.dx = 0;
    bullet.dy = 0;
    bullet.sx = 0;
    bullet.sy = 0;

}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
     SDL_Rect offset;
     offset.x = x;
     offset.y = y;

     SDL_BlitSurface(source, NULL, destination, &offset);
    
}

/*SDL_Surface* load_image(const char* filename)
{
   SDL_Surface* imgloaded = NULL;
   imgloaded = IMG_Load(filename);

   return imgloaded;
}*/

void draw_player(float srcX, float srcY, float dstX, float dstY, int width, int height, SDL_Surface* source, SDL_Surface* destination)
{
   SDL_Rect sourc, destino;
   sourc.x = srcX;
   sourc.y = srcY;
   sourc.w = width;
   sourc.h = height;

   destino.x = dstX;
   destino.y = dstY;
   destino.w = width;
   destino.h = height;

   SDL_BlitSurface(source, &sourc, destination, &destino);
}

void desenha_texto(char* texto, SDL_Surface* dst, int x, int y)
{
  SDL_Color cor = {255, 255, 255}; //vermelho
  SDL_Surface* src = TTF_RenderText_Blended(fonte, texto, cor);
  SDL_Rect dst_rect = {x, y, 0, 0};
  
  SDL_BlitSurface(src, NULL, dst, &dst_rect);
  
  SDL_FreeSurface(src);
}

void AST3_INIT_POSITION()
{
     crobat[0].dx = -45;
     crobat[1].dx = -45;
     crobat[1].dy = rand()%450;

     while(crobat[1].dy < 425)
     {
      crobat[1].dy = rand()%450;
     }

     crobat[2].dx = rand()%650;

     while(crobat[2].dx < 625)
     {
      crobat[2].dx = rand()%650;
     }


     crobat[3].dx = 650;

     while(crobat[3].dx <625)
     {
      crobat[3].dx = 650;
     }

     crobat[3].dy = rand()%450;

     while(crobat[3].dy <440)
     {
      crobat[3].dy = rand()%450;
     }

 
}

void CREATE_ASTEROIDS(PLAYER crobat[])
{
   int i, j, k;

   for(i=0; i<4; i++)
      {
        crobat[i].width = 192;
        crobat[i].height = 192;
        crobat[i].active = 1;
        crobat[i].sx = 0;
        crobat[i].sy = 0;
        crobat[i].dx = 0;
        crobat[i].dy = 0;

         for(j=0; j<2; j++)
         {
          crobat[i].golbat[j].width = 192;
          crobat[i].golbat[j].height = 192;
          crobat[i].golbat[j].active = 0;
          crobat[i].golbat[j].sx = 0;
          crobat[i].golbat[j].sy = 0;
          crobat[i].golbat[j].dx = 0;
          crobat[i].golbat[j].dy = 0;
         

          for(k=0; k<2; k++)
          {
           crobat[i].golbat[j].zubat[k].width = 192;
           crobat[i].golbat[j].zubat[k].height = 192;
           crobat[i].golbat[j].zubat[k].active = 0;
           crobat[i].golbat[j].zubat[k].sx = 0;
           crobat[i].golbat[j].zubat[k].sy = 0;
           crobat[i].golbat[j].zubat[k].dx = 0;
           crobat[i].golbat[j].zubat[k].dy = 0;

          }

        }
      }

   AST3_INIT_POSITION();
}

void SETUP_INIT()
{

    srand(time(NULL));
    CREATE_ASTEROIDS(crobat);
    PLAYER_INFO();

    SDL_Init(SDL_INIT_EVERYTHING);

    TTF_Init();

    LOAD_FILES();
    SDL_WM_SetIcon(icon, NULL);
    SDL_WM_SetCaption("Flying Warriors", NULL);
    SDL_EnableKeyRepeat(500, 30);
}

void draw_playerrect(PLAYER crobat1, SDL_Surface* source, SDL_Surface* destination)
{
   SDL_Rect sourc, destino;
   sourc.x = crobat1.sx;
   sourc.y = crobat1.sy;
   sourc.w = crobat1.width;
   sourc.h = crobat1.height;

   destino.x = crobat1.dx;
   destino.y = crobat1.dy;
   destino.w = crobat1.width;
   destino.h = crobat1.height;

   SDL_BlitSurface(source, &sourc, destination, &destino);
}

void draw_enemy2(PLAYER crobat1, int i, SDL_Surface* source, SDL_Surface* destination)
{
   SDL_Rect sourc, destino;
   sourc.x = crobat1.golbat[i].sx;
   sourc.y = crobat1.golbat[i].sy;
   sourc.w = crobat1.golbat[i].width;
   sourc.h = crobat1.golbat[i].height;

   destino.x = crobat1.golbat[i].dx;
   destino.y = crobat1.golbat[i].dy;
   destino.w = crobat1.golbat[i].width;
   destino.h = crobat1.golbat[i].height;

   SDL_BlitSurface(source, &sourc, destination, &destino);
}

void draw_enemy3(PLAYER crobat1, int i, int k, SDL_Surface* source, SDL_Surface* destination)
{
   SDL_Rect sourc, destino;
   sourc.x = crobat1.golbat[i].zubat[k].sx;
   sourc.y = crobat1.golbat[i].zubat[k].sy;
   sourc.w = crobat1.golbat[i].zubat[k].width;
   sourc.h = crobat1.golbat[i].zubat[k].height;

   destino.x = crobat1.golbat[i].zubat[k].dx;
   destino.y = crobat1.golbat[i].zubat[k].dy;
   destino.w = crobat1.golbat[i].zubat[k].width;
   destino.h = crobat1.golbat[i].zubat[k].height;

   SDL_BlitSurface(source, &sourc, destination, &destino);
}

void reverse (char s[]) 
{ 

  int i, j; char c;
  
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) { 
      
      c = s[i]; 
      s[i] = s[j]; 
      s[j] = c; 
    
    } 
}

void itoa(int n, char s[]) 
{ 
  int i, sign;
    
    if ((sign = n) < 0) 
      n = -n;
      i = 0; 
    
    do { 
      s[i++] = n % 10 + '0';
       } while ((n /= 10) > 0);


    if (sign < 0) 

      s[i] = '-';

        s[i] = '\0'; 

      reverse(s); 
} 

void UPDATE_LOCATION()
{
     int i, j, k;

     for(i=0; i<4; i++)
      {
         for(j=0; j<2; j++)
         {
        crobat[i].golbat[j].width = 192;
        crobat[i].golbat[j].height = 192;
        crobat[i].golbat[j].sx = 0;
        crobat[i].golbat[j].sy = 0;
        crobat[i].golbat[j].dx = crobat[i].dx;
        crobat[i].golbat[j].dy = crobat[i].dy;
         

          for(k=0; k<2; k++)
          {
             crobat[i].golbat[j].zubat[k].width = 192;
             crobat[i].golbat[j].zubat[k].height = 192;
             crobat[i].golbat[j].zubat[k].sx = 0;
             crobat[i].golbat[j].zubat[k].sy = 0;
             crobat[i].golbat[j].zubat[k].dx = crobat[i].dx;
             crobat[i].golbat[j].zubat[k].dy = crobat[i].dy;

          }

        }
      }
}


void ENEMY2_MOVING()
{
         int i, j;

      for(i=0; i<4; i++)
    {

      for(j=0; j<2; j++)
      {
        if(i<2)
        {
         crobat[i].golbat[0].dx += vel_crobat;
         crobat[i].golbat[0].dy += vel_crobat;
         crobat[i].golbat[1].dx += vel_crobat;
         crobat[i].golbat[1].dy -= vel_crobat;

    if(crobat[i].golbat[j].dx > 780)
    {
      crobat[i].golbat[j].dx = -45;
    }

    if(crobat[i].golbat[j].dy < -45)
    {
      crobat[i].golbat[j].dy = 450;
    }

    if(crobat[i].golbat[j].dy > 450)
    {
      crobat[i].golbat[j].dy = -45;
    }
       }

       else
       {
        crobat[i].golbat[0].dx -= vel_crobat;
        crobat[i].golbat[0].dy -= vel_crobat;
        crobat[i].golbat[1].dx -= vel_crobat;
        crobat[i].golbat[1].dy += vel_crobat;

            if(crobat[i].golbat[j].dx < -45)
    {
      crobat[i].golbat[j].dx = 780;
    }

    if(crobat[i].golbat[j].dy < -45)
    {
      crobat[i].golbat[j].dy = 450;
    }

    if(crobat[i].golbat[j].dy > 450)
    {
      crobat[i].golbat[j].dy = -45;
    }
       }

     }
    }
}

void ENEMY1_MOVING()
{
         int i, j, k;

      for(i=0; i<4; i++)
    {

      for(j=0; j<2; j++)
      {
         for(k=0; k<2; k++)
         {
        if(i<2)
        {
         crobat[i].golbat[j].zubat[0].dx += vel_crobat;
         crobat[i].golbat[j].zubat[0].dy += vel_crobat;
         crobat[i].golbat[j].zubat[1].dx += vel_crobat;
         crobat[i].golbat[j].zubat[1].dy -= vel_crobat;

    if(crobat[i].golbat[j].zubat[k].dx > 780)
    {
      crobat[i].golbat[j].zubat[k].dx = -45;
    }

    if(crobat[i].golbat[j].zubat[k].dy < -45)
    {
      crobat[i].golbat[j].zubat[k].dy = 450;
    }

    if(crobat[i].golbat[j].zubat[k].dy > 450)
    {
      crobat[i].golbat[j].zubat[k].dy = -45;
    }
       }

       else
       {
        crobat[i].golbat[j].zubat[0].dx -= vel_crobat*1.5;
        crobat[i].golbat[j].zubat[0].dy -= vel_crobat*1.5;
        crobat[i].golbat[j].zubat[1].dx -= vel_crobat*1.5;
        crobat[i].golbat[j].zubat[1].dy += vel_crobat*1.5;

            if(crobat[i].golbat[j].zubat[k].dx < -45)
    {
      crobat[i].golbat[j].zubat[k].dx = 780;
    }

    if(crobat[i].golbat[j].zubat[k].dy < -45)
    {
      crobat[i].golbat[j].zubat[k].dy = 450;
    }

    if(crobat[i].golbat[j].zubat[k].dy > 450)
    {
      crobat[i].golbat[j].zubat[k].dy = -45;
    }
       }
       }
     }
    }
}


float CHECK_WIDTH(PLAYER player)
{
                     if(player.dx > WIDTH)
                    {
                       player.dx = 0;
                        return player.dx;
                       
                    }

                    else if(player.dx < 0)
                    {
                        player.dx = WIDTH;
                         return player.dx;
                    }

                    else
                         {
                             return player.dx;
                         }
}

    float CHECK_HEIGHT(PLAYER player)
{
                     if(player.dy > HEIGHT)
                    {
                       player.dy = 0;
                        return player.dy;
                       
                    }

                    else if(player.dy < 0)
                    {
                        player.dy = HEIGHT;
                         return player.dy;
                    }

                    else
                         {
                             return player.dy;
                         }
}
  
void ENEMY3_MOVING()
{

  crobat[0].dx += vel_crobat;
  crobat[0].dy += vel_crobat;
  crobat[1].dx += vel_crobat;
  crobat[1].dy -= vel_crobat;
  crobat[2].dx -= vel_crobat;
  crobat[2].dy += vel_crobat;
  crobat[3].dx -= vel_crobat;
  crobat[3].dy -= vel_crobat;



  //printf("%f %f\n ", crobat[0].dx, crobat[0].dy);

  for(qnt_crobats = 0; qnt_crobats <4; qnt_crobats++)
  {
    if(crobat[qnt_crobats].dx < -45)
    {
      crobat[qnt_crobats].dx = 780;
    }

    if(crobat[qnt_crobats].dx > 780)
    {
      crobat[qnt_crobats].dx = -45;
    }

    if(crobat[qnt_crobats].dy < -45)
    {
      crobat[qnt_crobats].dy = 450;
    }

    if(crobat[qnt_crobats].dy > 450)
    {
      crobat[qnt_crobats].dy = -45;
    }
  }

}

 void ASTEROIDS_ON2(int asteroid)
 {
          //ASTEROIDE2_INFO();
    

         for(qnt_golbats=0; qnt_golbats<2; qnt_golbats++)
         {

            crobat[asteroid].golbat[qnt_golbats].sy += 192;

            if(crobat[asteroid].golbat[qnt_golbats].sy > 12096)
            {
              crobat[asteroid].golbat[qnt_golbats].sy = 0;
            }

            if(asteroid<2)
            {
              draw_enemy2(crobat[asteroid],qnt_golbats, enemy2left, screen);
            }

            if(asteroid >= 2)
            {
              draw_enemy2(crobat[asteroid],qnt_golbats, enemy2right, screen);
            }
         }
    
 }

 void ASTEROIDS_ON1(int i, int j)
 {
          //ASTEROIDE2_INFO();
     int k;

         for(k=0; k<2; k++)
         {

            crobat[i].golbat[j].zubat[k].sy += 192;

            if(crobat[i].golbat[j].zubat[k].sy > 7680)
            {
              crobat[i].golbat[j].zubat[k].sy = 0;
            }

            if(i<2)
            {
              draw_enemy3(crobat[i],j,k, enemy1left, screen);
            }

            if(i >= 2)
            {
              draw_enemy3(crobat[i],j,k, enemy1right, screen);
            }
         }
    
 }

   float SPEEDING(float vel)
{
   
                      if(vel<=20)
                     {
                          vel = vel+1;
                          return vel;
                          
                      }

                              else
                               {
                                  
                                  return vel;
                                
                                 }

                
}


 float FRAME_UPDATE_PLUS(PLAYER player)
{
                  player.sx +=53;
                 //direction -= 1;
                 

               // soux += 233;

                    if( player.sx > LASTFRAME)
                   {
                      player.sx -= 424;          
                   
                      return player.sx;
                   }

              return player.sx;
}

 float FRAME_UPDATE_MINUS(PLAYER player)
{
                  player.sx -=53;

                    if( player.sx < 0)
                   {
                      player.sx += 424;          
                   
                      return player.sx;
                   }

              return player.sx;
}

 float COLLISION(PLAYER bullet,PLAYER enemy)
{

 if( (bullet.dx >= enemy.dx+100 && bullet.dx <= (enemy.dx+100 + (enemy.width-160))) ||
      ((bullet.dx + bullet.width) >= enemy.dx+100 && (bullet.dx + bullet.width) <= (enemy.dx+100 + (enemy.width-160))) )
 {
    if( (bullet.dy >= enemy.dy+73 && bullet.dy <= (enemy.dy+73 + (enemy.height-133))) ||
        ((bullet.dy + bullet.height) >= enemy.dy+73 && (bullet.dy + bullet.height) <= (enemy.dy+73 + (enemy.height-133))) )
    {
         return 1;
    }

  }

  else{
       return 0;
       }

}

 float COLLISION2(PLAYER bullet, PLAYER enemy, int i)
 {
   if( (bullet.dx >= enemy.golbat[i].dx+85 && bullet.dx <= (enemy.golbat[i].dx+85 + (enemy.golbat[i].width-145))) ||
      ((bullet.dx + bullet.width) >= enemy.golbat[i].dx+85 && (bullet.dx + bullet.width) <= (enemy.golbat[i].dx+85 + (enemy.golbat[i].width-145))) )
 {
    if( (bullet.dy >= enemy.golbat[i].dy+73 && bullet.dy <= (enemy.golbat[i].dy+73 + (enemy.golbat[i].height-133))) ||
        ((bullet.dy + bullet.height) >= enemy.golbat[i].dy+73 && (bullet.dy + bullet.height) <= (enemy.golbat[i].dy+73 + (enemy.golbat[i].height-133))) )
    {
         return 2;
    }

  }

  else
       return 0;
 }

  float COLLISION3(PLAYER bullet, PLAYER enemy, int i, int j)
 {
   if( (bullet.dx >= enemy.golbat[i].zubat[j].dx+173 && bullet.dx <= (enemy.golbat[i].zubat[j].dx+73 + (enemy.golbat[i].zubat[j].width-133))) ||
      ((bullet.dx + bullet.width) >= enemy.golbat[i].zubat[j].dx+73 && (bullet.dx + bullet.width) <= (enemy.golbat[i].zubat[j].dx+73 + (enemy.golbat[i].zubat[j].width-133))) )
 {
    if( (bullet.dy >= enemy.golbat[i].zubat[j].dy+73 && bullet.dy <= (enemy.golbat[i].zubat[j].dy+73 + (enemy.golbat[i].zubat[j].height-133))) ||
        ((bullet.dy + bullet.height) >= enemy.golbat[i].zubat[j].dy+73 && (bullet.dy + bullet.height) <= (enemy.golbat[i].zubat[j].dy+73 + (enemy.golbat[i].zubat[j].height-133))) )
    {
         return 3;
    }

  }

  else
       return 0;
 }

  /*   float COLLISION( PLAYER A, PLAYER B )
{
  if (  A.dx     < B.dx + B.width   &&
    A.dx + A.width   >   B.dx     &&
    A.dy   < B.dy + B.height   &&
    A.dy + A.height > B.dy )
  {
    return 3;
  }
  
}*/

void CHECK_COLISION()
{

      for(qnt_crobats =0; qnt_crobats<4; qnt_crobats++)
    {   

            int j, k;

       for(j=0; j<2; j++)
       {
          for(k=0; k<2; k++)
          {
            if(COLLISION(bullet, crobat[qnt_crobats]) == 1)
           {    //The sprites appear to overlap.
               if(collision_on != 0)
              {
               collision_on = collision_on;
              }

               else{
               collision_on += 1;
               }

              if(collision_on == 1)
             {
              change += 1;
 
              tiro = 0;
              hero = IMG_Load("zp.png");
              movebullet = IMG_Load("zapp.png");
              contador_tiro = 0;

          //ASTEROIDE2_INFO();
          //ASTEROIDS_ON2(asteroid);
          //ASTEROIDE3_INFO();
              pont += 40;
              crobat[qnt_crobats].active = 0;
              crobat[qnt_crobats].width = 0;
              crobat[qnt_crobats].height = 0;
              crobat[qnt_crobats].golbat[0].active = 1;
              crobat[qnt_crobats].golbat[1].active = 1;
              all_enemies -= 1;

              if(change > 1)
             { 
              change = 0;
              tiro = 0;
              contador_tiro = 0;
              hero = IMG_Load("latiossheet.png");
              movebullet = IMG_Load("bulletsheet.png");
              }
             }
          }

    //collision_on = 0;

           if(!crobat[qnt_crobats].active)
          {
            if(COLLISION2(bullet, crobat[qnt_crobats], j) == 2)
           {

               if(collision_on != 0 )
              {
                collision_on = collision_on;
              }

              else{
               collision_on += 2;
              }
        
              if(collision_on == 2)
             {
              tiro = 0;
              contador_tiro = 0;
              pont += 20;
          //collision_on = 1;
              all_enemies -= 1;
              crobat[qnt_crobats].golbat[j].active = 0;
          //crobat[qnt_crobats].golbat[j].active = 0;
          //crobat[qnt_crobats].golbat[j].active = 0;
              crobat[qnt_crobats].golbat[j].width = 0;
              crobat[qnt_crobats].golbat[j].height = 0;
              crobat[qnt_crobats].golbat[j].dx = 0;
              crobat[qnt_crobats].golbat[j].dy = 0;  
              crobat[qnt_crobats].golbat[j].zubat[0].active = 1;
              crobat[qnt_crobats].golbat[j].zubat[1].active = 1;
             }
           }
          }

if(!crobat[qnt_crobats].active && !crobat[qnt_crobats].golbat[j].active)
{
  if(COLLISION3(bullet, crobat[qnt_crobats], j, k) == 3)
  {

       if(collision_on != 0)
       {
         collision_on = collision_on;
       }
        else{
          collision_on += 3;
        }

          if(collision_on == 3)
          {
          tiro = 0;
          contador_tiro = 0;
          pont += 10;
          all_enemies -= 1;
          crobat[qnt_crobats].golbat[j].zubat[k].active = 0;
          //crobat[qnt_crobats].golbat[j].zubat[k].active = 0;
          //crobat[qnt_crobats].golbat[j].zubat[k].active = 0;
          crobat[qnt_crobats].golbat[j].zubat[k].width = 0;
          crobat[qnt_crobats].golbat[j].zubat[k].height = 0; 
          crobat[qnt_crobats].golbat[j].zubat[k].dx = 0;
          crobat[qnt_crobats].golbat[j].zubat[k].dy = 0;
      }
  }

}
  
}
  }  
  collision_on = 0;
}
}


float FRAME_BULLET(int bullet)
{
      switch(bullet)
      {
        case 0: return 0;
                break;

        case 1: return 0;
                break;

        case 2: return 371;
                break;

        case 3: return 318;
                break;

        case 4: return 265;
                break;

        case 5: return 212;
                break;
      
        case 6: return 159;
                break;

        case 7: return 106;
                break;

        default: return 53;
                 break;
     }
}

float DIRX(int dir, PLAYER player, float vel)
{
       switch(dir)
      {
         case 1: player.dx += 0;
                 return CHECK_WIDTH(player);
                 break;

         case 2: player.dx += vel;
                 return CHECK_WIDTH(player);
                 break;

         case 3: player.dx += vel;
                 return CHECK_WIDTH(player);
                 break;

         case 4: player.dx += vel;
                 return CHECK_WIDTH(player);
                 break;

         case 5: player.dx += 0;
                 return CHECK_WIDTH(player);
                 break;

         case 6: player.dx -= vel;
                 return CHECK_WIDTH(player);
                 break;

         case 7: player.dx -= vel;
                 return CHECK_WIDTH(player);
                 break;

         default: player.dx -= vel;
                  return CHECK_WIDTH(player);
                  break;

        }
}

float DIRY(int dir, PLAYER player, float vel)
{
       switch(dir)
      {
         case 1: player.dy -= vel;
                 return CHECK_HEIGHT(player);
                 break;

         case 2: player.dy -= vel;
                 return CHECK_HEIGHT(player);
                 break;

         case 3: player.dy += 0;
                 return CHECK_HEIGHT(player);
                 break;

         case 4: player.dy += vel;
                 return CHECK_HEIGHT(player);
                 break;

         case 5: player.dy += vel;
                 return CHECK_HEIGHT(player);
                 break;

         case 6: player.dy += vel;
                 return CHECK_HEIGHT(player);
                 break;

         case 7: player.dy += 0;
                 return CHECK_HEIGHT(player);
                 break;

         default: player.dy -= vel;
                 return CHECK_HEIGHT(player);
                 break;

        }
}

void DOBULLET()
{
            if(tiro == 0)
           {
             bullet.dx = player.dx;
             bullet.dy = player.dy;
           }

          if(tiro>0)
           {
                bullet.sx = FRAME_BULLET(tiro);
                bullet.dx = DIRX(tiro, bullet, vel_tiro);
                bullet.dy = DIRY(tiro, bullet, vel_tiro);
                contador_tiro++;
                draw_playerrect(bullet, movebullet, screen);
            
               if(contador_tiro>=20)
              {
               tiro = 0;
               contador_tiro = 0;
              }

           }
}

void DECELERATION()
{
            if(solta != 0)
         {
                //sx = FRAME_BULLET(solta);
                solta = direction +1;
                player.dx = DIRX(solta, player, vel);
                player.dy = DIRY(solta, player, vel);
                vel -=1;
            
            
                if(vel == 0)
              {
               solta = 0;
               }

               if(vel < 0)
               {
                vel = 0;
                solta = 0;
               }
           }
}

void DOENEMIES()
{
          for(qnt_crobats = 0; qnt_crobats < 4; qnt_crobats++)
        {
           crobat[qnt_crobats].sy += 192;

                         if( crobat[qnt_crobats].sy > 5376)
             {
               crobat[qnt_crobats].sy = 0;
             }

           if(qnt_crobats < 2)
           {
           draw_playerrect(crobat[qnt_crobats], enemy3left, screen);
           }

           else{
            draw_playerrect(crobat[qnt_crobats], enemy3, screen);
           }

         }
   
}


void KEYSTATE()
{
    if( SDL_PollEvent(&event))
   { 
        if(event.type == SDL_QUIT)
       {
           gamerunning = 0;
       }

           if(event.type == SDL_KEYDOWN)
          {

             switch(event.key.keysym.sym)
             {

              case SDLK_ESCAPE:
                    SDL_Quit();
                    break;

              case SDLK_LEFT: leftleft = 0;
                              break;

              case SDLK_RIGHT: rightright = 0;
                               break;

              case SDLK_UP: upup = 0;
                            break;

              case SDLK_SPACE: if( tiro != 0)
                                 { 
                                   tiro = tiro;
                                 }

                                 else{
                                   tiro = (direction+1);
                                 }
                                 break;
              }

 }
           if(event.type == SDL_KEYUP)
          {

             switch(event.key.keysym.sym)
             {
                case SDLK_UP: upup = 1;
                              solta = direction +1;
                              break;

                case SDLK_LEFT: leftleft = 1;
                                break;

                case SDLK_RIGHT: rightright = 1;
                                 break;

              }
          }
 }

            if(!upup)
           {
                  if(solta != 0)
                                   {
                                     solta = 0;
                                    }
                     vel = SPEEDING(vel);
                     player.dx = DIRX(direction+1, player, vel);
                     player.dy = DIRY(direction+1, player, vel);
           }

                     if(!leftleft)
          {
                    player.sx = FRAME_UPDATE_PLUS(player);
                    direction -= 1;;
                    if( direction < 0)
                   {
                        direction += 8;
                   }

          }

          if(!rightright)
          {
                    player.sx = FRAME_UPDATE_MINUS(player);
                    direction += 1;
                    if( direction > 7)
                   {
                     direction -= 8;
                   }
          }
}

void ENEMY_POSITION()
{

    int i, j, k;



    for(i=0; i<4; i++)
    {   for(j=0; j<2; j++)
        {
         for(k=0; k<2; k++)
        { 
         if(crobat[i].active)
       {
         //UPDATE_LOCATION();
        crobat[i].golbat[j].dx = 20+crobat[i].dx ;
        crobat[i].golbat[j].dy = 20+crobat[i].dy ;
       }
        

      if(!crobat[i].active)
      {
        crobat[i].width = 0;
        crobat[i].height = 0;
        //crobat[i].active = 1;
        crobat[i].sx = 0;
        crobat[i].sy = 0;
        crobat[i].dx = 0;
        crobat[i].dy = 0;
      }

       if(crobat[i].golbat[0].active == 1 || crobat[i].golbat[0].active == 1)
       {
         ASTEROIDS_ON2(i);
        //crobat[i].golbat[j].zubat[k].sx = 0;
        //crobat[i].golbat[j].zubat[k].sy = 0;
        crobat[i].golbat[j].zubat[k].dx = 30 + crobat[i].golbat[j].dx ;
        crobat[i].golbat[j].zubat[k].dy = 30 + crobat[i].golbat[j].dy ;
        //crobat[i].golbat[j].zubat[1].dx = 30 + crobat[i].golbat[j].dx ;
        //crobat[i].golbat[j].zubat[1].dy = 30 + crobat[i].golbat[j].dy ;

       }


        if(crobat[i].golbat[j].zubat[0].active == 1) //|| //crobat[i].golbat[j].zubat[1].active == 1)
        {

          ASTEROIDS_ON1(i, j);
        }
     
        }
    }
  }

}

void CLEAN_UP()
{
SDL_FreeSurface(intro);
SDL_FreeSurface(icon);
SDL_FreeSurface(hero);
SDL_FreeSurface(enemy1right);
SDL_FreeSurface(enemy1left);
SDL_FreeSurface(enemy2right);
SDL_FreeSurface(enemy2left);
SDL_FreeSurface(enemy3);
SDL_FreeSurface(enemy3left);
SDL_FreeSurface(movebullet);
SDL_FreeSurface(background);

}

void ENEMIES_DEAD()
{

  if(all_enemies < 0)
  {
    all_enemies == 0;
  }
     if(all_enemies == 0)
     {
       all_enemies = 28;
       CREATE_ASTEROIDS(crobat);
     }

     if(all_enemies > 0)
     {
       DOENEMIES();
       ENEMY3_MOVING();
       ENEMY2_MOVING();
       ENEMY1_MOVING();
       ENEMY_POSITION();
     }
}

void QUITTING()
{
  TTF_Quit();
  SDL_Quit();
}


int main(int argc, char** args)
{
     SETUP_INIT();
     Mix_VolumeMusic(128);
    Mix_PlayMusic(fase1, -1);

    int FPS = 29;
    int interval = 1*1000 / FPS ; 
    int currentTick;
    int maxFPS = 100;

    while(gamerunning)
{
       apply_surface ( 0, 0, background, screen );
       itoa(pont, ponts);
       desenha_texto(ponts, screen, 300, 0);
       desenha_texto("pontos : ", screen, 180, 0);

       if(pont == 1000)
       {
        fase1 = Mix_LoadMUS("selectcharacter.mp3");
       }
              ENEMIES_DEAD();
       //DOENEMIES();
       //ENEMY3_MOVING();
       //apply_surface(0, 0, top, screen);
       //draw_player( frame_largura, frame_altura, destinox, destinoy, width, height, background, screen);

       DOBULLET();
       DECELERATION();
       CHECK_COLISION();
       //ENEMY2_MOVING();
       //ENEMY_POSITION();
       KEYSTATE();
       //ENEMY1_MOVING();
      printf("%d\n", all_enemies);


      //draw_player( soux, souy, desx, desy, enewi, enehe, enemy3, screen);
          // draw_player( srcx, srcy, dstx, dsty, sprite_width, sprite_height, hero, screen);
       draw_playerrect(player, hero, screen);
           //draw_player( xs, ys, xd, yd, w, h, intro, screen);
           //SDL_UpdateRect(screen, 0, 0, 0, 0);
         currentTick = SDL_GetTicks();
  // ... Program stuff

  // Check FPS rate
  if ( SDL_GetTicks() - interval < interval )
  {
    SDL_Delay( (int)(interval - (SDL_GetTicks() - currentTick)) );
  }
       SDL_Flip( screen);

           if( SDL_Flip(screen) == -1)
          {
           return 1;
          }
}

      CLEAN_UP();
      QUITTING();

     return 0;
}