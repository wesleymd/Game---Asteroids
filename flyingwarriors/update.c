#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#define MAX_PONTS 100000
#define MAX_ARRAY 100
#define MAX_NOME 12

const int WIDTH = 800; //960
const int HEIGHT = 600; //557
const int BPP = 32;
//const int FRAMES_PER_SECOND = 20;

     FILE * p_arquivo;
     

float vel_crobat = 1.75;
int upup = 1;
int leftleft = 1;
int rightright = 1;
int typingname = 0;

int girar = 0;
int x, y;
int numtiro = 0;

void ENTER_NAME();
int ranking = 0;
int revive = 0;
int ast2 = 0;
int qnt_recorde = 0;
int asteroid = 0;
int collision_on = 0;
int name_typed = 0, initials =0;
char namename[100];
int pont = 0;
char ponts[MAX_PONTS];
int all_enemies = 28;
char enemies_rest[MAX_PONTS];
int lives = 3;
int menu_op = 0;
int musicloop = 10;
int delete = 28;
int choose_char = 0;
int volume_on = 0;
int instructions = 0;
char lifebar[MAX_PONTS];
char nameplayer[100];
float speedgolbat = 1.16, speedzubat = 1.25;




#define NUMSPRITES 8
#define FPS 30

SDL_Surface* intro = NULL;
SDL_Surface* icon = NULL;
SDL_Surface* logo = NULL;
SDL_Surface* highscore = NULL;
SDL_Surface* soundoff = NULL;
SDL_Surface* lifeimg = NULL;
SDL_Surface* explosion_frame = NULL;
SDL_Surface* menu = NULL;
SDL_Surface* boss = NULL;
SDL_Surface* continuegame = NULL;
TTF_Font* fonte_solid = NULL;
TTF_Font* fonte = NULL;
TTF_Font* fontesmall = NULL;
TTF_Font* fontesmall2 = NULL;
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
Mix_Chunk* cryplayer = NULL;
Mix_Chunk* crycrobat = NULL;
Mix_Chunk* crygolbat = NULL;
Mix_Chunk* cryzubat = NULL;
Mix_Music* fase1 = NULL;
Mix_Chunk* select_option = NULL;
Mix_Chunk* choose_option = NULL;
Mix_Chunk* back_option = NULL;
Mix_Chunk* delete_option = NULL;
Mix_Chunk* type_option = NULL;

Mix_Chunk* lowhp = NULL;

#define LASTFRAME 371



SDL_Event event;

int gamerunning = 1;

typedef struct _ASTEROIDE1
{

  int width;
  int height;
  int active;
  int burst;
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
  int burst;
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
  int burst;
  float sx;
  float sy;
  float dx;
  float dy;
  GOLBAT golbat[2];

}PLAYER;

typedef struct _ENEMY2
{

  int width;
  int height;
  int active;
  int burst;
  float sx;
  float sy;
  float dx;
  float dy;
  //GOLBAT golbat[2];

}ENEMY2;

typedef struct _ENEMY
{

  int width;
  int height;
  int active;
  int burst;
  float sx;
  float sy;
  float dx;
  float dy;
  ENEMY2 ast2[2];

}ENEMY;

//ENEMY solrock[2], lunatone[2], creselia, beheeyem[2], giratina; 

PLAYER player, bullet, firebullet[4], opening;
PLAYER crobat[4], explosion[4];

  typedef struct
  {
      char nome[MAX_NOME];
      int pontuacao;
  } RECORDE;

  typedef struct
  {
      RECORDE vetor[MAX_ARRAY];
      int n;

  } ARRAY;

     int start_game = 0;
     int col = 0;
     int direction = 0;
     float vel = 0;
     float vel_tiro = 30;
     int qnt_crobats = 0;
     int qnt_golbats = 0;
     int qnt_zubats = 0;
     int asteroid_level[4];
     int contador_tiro = 0, solta = 0, tiro = 0, change = 0;
     int quantiro = 0;
     int character_screen = 0;
     int cont;

     int i=0;
     int fire[4] = {0, 0, 0, 0};
     int contador[4];

      RECORDE record;
      ARRAY array, arraynew;

      char pontsrec[100];

void insere(ARRAY *array, RECORDE recorde);

void LOAD_FILES()
{
    p_arquivo = fopen("recordes.bin", "rb");
    
    if(fopen("recordes.bin", "rb") != NULL)
    {
    fread(&array, sizeof(ARRAY), 1, p_arquivo);
    insere(&array, record);
    arraynew = array;
    }

    else{
      array.n = 0;
    }

    
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 );
    //Mix_PlayChannel(1, cryplayer, -1);
    //Mix_PlayChannel(2, crycrobat, -1);
    //Mix_PlayChannel(2, crygolbat, -1);
    //Mix_PlayChannel(2, cryzubat, -1);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);
    icon = SDL_LoadBMP("ball.bmp");
    intro = IMG_Load("backgrounds/intro.png");
    fonte = TTF_OpenFont("fonts/pokemonhollow.ttf", 26);
    fonte_solid = TTF_OpenFont("fonts/Pokemon Solid.ttf", 25);
    fontesmall = TTF_OpenFont("fonts/Pokemon Solid.ttf", 13);
    fontesmall2 = TTF_OpenFont("fonts/pokemonhollow.ttf", 14);
    pontos = fonte;
    menu = IMG_Load("backgrounds/start_game.jpg");
    //lifeimg = IMG_Load("backgrounds/lifes.png");
    soundoff = IMG_Load("backgrounds/soundoff.png");
    crycrobat = Mix_LoadWAV("sounds/crobat.wav");
    crygolbat = Mix_LoadWAV("sounds/golbat.wav");
    cryzubat =  Mix_LoadWAV("sounds/zubat.wav");
    select_option = Mix_LoadWAV("sounds/select.wav");
    choose_option = Mix_LoadWAV("sounds/ok.wav");
    back_option = Mix_LoadWAV("sounds/back.wav");
    delete_option = Mix_LoadWAV("sounds/delete.wav");
    type_option = Mix_LoadWAV("sounds/type.wav");
    lowhp = Mix_LoadWAV("sounds/lowhp.wav");
    logo = IMG_Load("backgrounds/logo.png");
    highscore = IMG_Load("backgrounds/highscores.jpg");
    movebullet = IMG_Load("player/articunobullet.png");
    continuegame = IMG_Load("backgrounds/highscores.jpg");
    fase1 = Mix_LoadMUS("sounds/menu.mp3");
    hero = IMG_Load("player/articunosheet.png");
    explosion_frame = IMG_Load("enemies/explosion.png");
    enemy1right = IMG_Load("enemies/zubatright.png");
    enemy1left = IMG_Load("enemies/zubatleft.png");
    enemy2left = IMG_Load("enemies/golbatleft.png");
    enemy2right = IMG_Load("enemies/golbat.png");
    enemy3 = IMG_Load("enemies/crobatsheet.png");
    enemy3left = IMG_Load("enemies/crobatleft.png");
    background = IMG_Load("backgrounds/pokemonuniverse.jpg");

}

void PLAYER_INFO()
{

    direction = 0;
    vel = 0;
    
    player.active = 1;
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

    int i;

    for(i=0; i<4; i++)
    {
      firebullet[i].width = 53;
    firebullet[i].height = 53;
    firebullet[i].dx = 0;
    firebullet[i].dy = 0;
    firebullet[i].sx = 0;
    firebullet[i].sy = 0;
    firebullet[i].active = 0;
    }

   
}

void EXPLOSION_INFO()
{
  int i, j, k;

  for(i=0; i<4; i++)
  {  
      explosion[i].width = 192;
      explosion[i].height = 192;
      explosion[i].sx = 0;
      explosion[i].sy = 0;
      explosion[i].dx = 0;
      explosion[i].dy = 0;




    for(j=0; j<2; j++)
     {  

      explosion[i].golbat[j].width = 192;
      explosion[i].golbat[j].height = 192;
      explosion[i].golbat[j].sx = 0;
      explosion[i].golbat[j].sy = 0;
      explosion[i].golbat[j].dx = 0;
      explosion[i].golbat[j].dy = 0;


      for(k=0; k<2; k++)
         {

          explosion[i].golbat[j].zubat[k].width = 192;
          explosion[i].golbat[j].zubat[k].height = 192;
          explosion[i].golbat[j].zubat[k].sx = 0;
          explosion[i].golbat[j].zubat[k].sy = 0;
          explosion[i].golbat[j].zubat[k].dx = 0;
          explosion[i].golbat[j].zubat[k].dy = 0;

         }

       }

  }
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

void draw_text(char* texto, TTF_Font* font, SDL_Surface* dst, int x, int y, int r, int g, int b)
{
  SDL_Color cor = {r, g, b}; //vermelho
  SDL_Surface* src = TTF_RenderText_Blended(font, texto, cor);
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

void MENU_IMAGES()
{
               if(menu_op == 0)
             {
                   menu = IMG_Load("backgrounds/start_game.jpg");
                   apply_surface(0, 0, menu, screen);
                   draw_text("Start", fonte, screen, 20, 160, 0, 0, 255);
                   draw_text("Start", fonte_solid, screen, 20, 160, 255, 255, 0);
              }

               if(menu_op == 1)
              {
                   menu = IMG_Load("backgrounds/ranking.jpg");
                   apply_surface(0, 0, menu, screen);
                   draw_text("Ranking", fonte, screen, 220, 240, 0, 0, 255);
                   draw_text("Ranking", fonte_solid, screen, 220, 240, 255, 255, 0);
               }

               if(menu_op == 2)
              {
                   menu = IMG_Load("backgrounds/settings.jpg");
                   apply_surface(0, 0, menu, screen);
                   draw_text("Audio", fonte, screen, 330, 360, 0, 0, 255);
                   draw_text("Audio", fonte_solid, screen, 330, 360, 255, 255, 0);
               }


               if(menu_op == 3)
              {
                   menu = IMG_Load("backgrounds/quit.jpg");
                   apply_surface(0, 0, menu, screen);
                   draw_text("Instructions", fonte, screen, 350, 490, 0, 0, 255);
                   draw_text("Instructions", fonte_solid, screen, 350, 490, 255, 255, 0);
               }

                  draw_text("Press Esc to quit game", fonte_solid, screen, 260, 550, 255, 255, 0);
   draw_text("Press Esc to quit game", fonte, screen, 260, 550, 0, 0, 255);
}

void CHOOSE_PLAYER()
{ 

   

  switch(choose_char)
  {
    case 1: menu = IMG_Load("backgrounds/char2.jpg");
            hero = IMG_Load("player/latiassheet.png");
            movebullet = IMG_Load("player/latiasbullet.png");
            lifeimg = IMG_Load("backgrounds/latias.png");
            cryplayer = Mix_LoadWAV("sounds/latios.wav");
            apply_surface(0, 0, menu, screen);
            break;
          
            case 0: menu = IMG_Load("backgrounds/char1.jpg");
            hero = IMG_Load("player/latiossheet.png");
            movebullet = IMG_Load("player/latiosbullet.png");
            lifeimg = IMG_Load("backgrounds/latios.png");
            cryplayer = Mix_LoadWAV("sounds/latias.wav");
            apply_surface(0, 0, menu, screen);
            break;

            case 2: menu = IMG_Load("backgrounds/char3.jpg");
            hero = IMG_Load("player/articunosheet.png");
            movebullet = IMG_Load("player/articunobullet.png");
            lifeimg = IMG_Load("backgrounds/articuno.png");
            cryplayer = Mix_LoadWAV("sounds/articuno.wav");
            apply_surface(0, 0, menu, screen);
            break;

            case 4: menu = IMG_Load("backgrounds/char5.jpg");
            hero = IMG_Load("player/zapdossheet.png");
            movebullet = IMG_Load("player/zapdosbullet.png");
            lifeimg = IMG_Load("backgrounds/zapdos.png");
            cryplayer = Mix_LoadWAV("sounds/zapdos.wav");
            apply_surface(0, 0, menu, screen);
            break;

            case 3: menu = IMG_Load("backgrounds/char4.jpg");
            hero = IMG_Load("player/moltressheet.png");
            movebullet = IMG_Load("player/moltresbullet.png");
            lifeimg = IMG_Load("backgrounds/moltres.png");
            cryplayer = Mix_LoadWAV("sounds/moltres.wav");
            apply_surface(0, 0, menu, screen);
            break;
  }

}

void MENU_KEYSTATE()
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

               case SDLK_RIGHT:

                            if(character_screen == 0)
             { menu_op += 1;
              Mix_PlayChannel(7, choose_option, 0);


                if( menu_op >3)
               {
                 menu_op = 0;
                }

              }


                 else
                 {
                   choose_char += 1;
                   Mix_PlayChannel(4, cryplayer, 0);

                    if(choose_char>4)
                    {
                      choose_char = 0;
                    }
                 }

                    break;

              case SDLK_LEFT: 

                             if(character_screen == 0)
              { menu_op -=1;
                Mix_PlayChannel(7, choose_option, 0);

                  if(menu_op < 0)
               {
                  menu_op  += 4;
                }
              }

                else
                 {
                    choose_char -= 1;
                    Mix_PlayChannel(4, cryplayer, 0);

                    if(choose_char<0)
                    {
                      choose_char = 4;
                    }
                  }
                    break;


               case SDLK_RETURN: 

               

               if(menu_op == 0)
               {
                
                if(character_screen == 1)
              {
                menu_op = 0;
                start_game = 1;
                lives = 3;
                upup = 1;
                leftleft = 1;
                rightright = 1;
                character_screen = 0;
                
                PLAYER_INFO();
                fase1 = Mix_LoadMUS("sounds/asteroid.mp3");
                Mix_HaltMusic();
               }

                else
                  {character_screen = 1;
                
                ranking = 0;
                fase1 = Mix_LoadMUS("sounds/playerselect.mp3");
                Mix_HaltMusic(); 
                }              
               }

               if(menu_op == 1)
               {
                  if(ranking ==1)
                {
                  ranking= 0;
                  menu_op = 1;
                }
                

                else{
                ranking = 1;
                   }
               }

               if(menu_op == 2)
               {

                  volume_on++;

                  if(volume_on>1)
                {
                  volume_on = 0;
                }    

                if(volume_on == 0)
                {
                  Mix_RewindMusic();
                Mix_VolumeMusic(128);
                }

                if(volume_on == 1)
                {
                  Mix_VolumeMusic(0);
                  
                } 

               }

               if(menu_op == 3)
               {
                

                if(instructions ==1)
                {
                  instructions = 0;
                  menu_op = 3;
                }

                else{
                  instructions =1;
                }
                
               }

               Mix_PlayChannel(6, select_option, 0);

               break;



                case SDLK_ESCAPE:

                if(character_screen == 1)
              {
                character_screen = 0;
                ranking = 0;
                menu_op = 0;
                fase1 = Mix_LoadMUS("sounds/menu.mp3");
                Mix_HaltMusic();     
              }




              else if(ranking == 1)
               {
                ranking = 0;
                menu_op = 1;
               }

               else if(instructions ==1)
                {
                  instructions = 0;
                  menu_op = 3;
                }


              else{
                exit(0);
              }

               Mix_PlayChannel(8, back_option, 0);
                break;

             }

         }

   }
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
         crobat[i].golbat[0].dx += vel_crobat*speedgolbat;
         crobat[i].golbat[0].dy += vel_crobat*speedgolbat;
         crobat[i].golbat[1].dx += vel_crobat*speedgolbat;
         crobat[i].golbat[1].dy -= vel_crobat*speedgolbat;

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
        crobat[i].golbat[0].dx -= vel_crobat*speedgolbat;
        crobat[i].golbat[0].dy -= vel_crobat*speedgolbat;
        crobat[i].golbat[1].dx -= vel_crobat*speedgolbat;
        crobat[i].golbat[1].dy += vel_crobat*speedgolbat;

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
         crobat[i].golbat[j].zubat[0].dx += vel_crobat*speedzubat;
         crobat[i].golbat[j].zubat[0].dy += vel_crobat*speedzubat;
         crobat[i].golbat[j].zubat[1].dx += vel_crobat*speedzubat;
         crobat[i].golbat[j].zubat[1].dy -= vel_crobat*speedzubat;

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
        crobat[i].golbat[j].zubat[0].dx -= vel_crobat*speedzubat;
        crobat[i].golbat[j].zubat[0].dy -= vel_crobat*speedzubat;
        crobat[i].golbat[j].zubat[1].dx -= vel_crobat*speedzubat;
        crobat[i].golbat[j].zubat[1].dy += vel_crobat*speedzubat;

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

  for(qnt_crobats = 0; qnt_crobats < 4; qnt_crobats++)
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
     int k;

         for(k=0; k<2; k++)
         {

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
                      if(vel<=40)
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

void CLEAR_STATUS(PLAYER crobat[],int i, int j, int k, int collision)
{
     if(collision == 1)
     {
              crobat[i].active = 0;
              crobat[i].width = 0;
              crobat[i].height = 0;
              crobat[i].dx = 0;
              crobat[i].dy = 0;
              all_enemies -= 1;
              contador_tiro = 0;
              tiro = 0;
              //pont += 40;
     }

          if(collision == 2)
     {
              crobat[i].golbat[j].active = 0;
              crobat[i].golbat[j].width = 0;
              crobat[i].golbat[j].height = 0;
              crobat[i].golbat[j].dx = 0;
              crobat[i].golbat[j].dy = 0;
              all_enemies -= 1;
              contador_tiro = 0;
              tiro = 0;
              //pont += 20;
     }

          if(collision == 3)
     {
              crobat[i].golbat[j].zubat[k].active = 0;
              crobat[i].golbat[j].zubat[k].width = 0;
              crobat[i].golbat[j].zubat[k].height = 0;
              crobat[i].golbat[j].zubat[k].dx = 0;
              crobat[i].golbat[j].zubat[k].dy = 0;
              all_enemies -= 1;
              contador_tiro = 0;
              tiro = 0;
              //pont += 10;
     }

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

void CHECK_COLISION()
{
        int i, j, k, numbullet;



      for(i =0; i<4; i++)
    {   

            //int i, j, k;

       for(j=0; j<2; j++)
       {
          for(k=0; k<2; k++)
          {

            for(numbullet =0; numbullet<4; numbullet++)
           {
              if(tiro != 0 && COLLISION(firebullet[numbullet], crobat[i]) == 1 && (firebullet[numbullet].dx != player.dx && firebullet[numbullet].dy != player.dy || firebullet[numbullet].dx == player.dx  && firebullet[numbullet].dy != player.dy || firebullet[numbullet].dx != player.dx && firebullet[numbullet].dy == player.dy))
            {    
               if(collision_on != 0)
              {
               collision_on = collision_on;
              }

               else{
               collision_on = 1;
               }

              if(collision_on == 1)
             {
       
              CLEAR_STATUS(crobat,i, j, k, collision_on);
              Mix_PlayChannel(1, crycrobat, 0);

              pont += 40;
              fire[numbullet] = 0;
              contador[numbullet] = 0;
              explosion[i].burst = 1;
              crobat[i].golbat[0].active = 1;
              crobat[i].golbat[1].active = 1;
              //all_enemies -= 1;


             }
          }

            if(player.active  == 1)
          {
            if(COLLISION(player, crobat[i]) == 1)
            {col = 1;
             CLEAR_STATUS(crobat, i, j, k, col);
             Mix_PlayChannel(1, crycrobat, 0);
             Mix_PlayChannel(4, cryplayer, 0);

             pont += 40;
            //crobat[i].active = 0;
            crobat[i].golbat[0].active = 1;
            crobat[i].golbat[1].active = 1;
            explosion[i].burst = 1;
              //all_enemies -= 1;
            player.active = 0;
            player.width = 0;
            player.height = 0;
            lives -= 1;
            direction = 0;
            tiro = 0;
            vel = 0;
            solta = 0;
           }

       }

    //collision_on = 0;

           if(!crobat[i].active )
          {
            if(tiro != 0 && COLLISION2(firebullet[numbullet], crobat[i], j) == 2 && ((firebullet[numbullet].dx != player.dx && firebullet[numbullet].dy != player.dy || firebullet[numbullet].dx == player.dx && firebullet[numbullet].dy != player.dy || firebullet[numbullet].dx != player.dx  && firebullet[numbullet].dy == player.dy)))
           {

               if(collision_on != 0 )
              {
                collision_on = collision_on;
              }

              else{
               collision_on = 2;
              }
        
              if(collision_on == 2)
             {
              CLEAR_STATUS(crobat, i, j, k, collision_on);
              Mix_PlayChannel(2, crygolbat, 0);

              pont += 20;
              fire[numbullet] = 0;
              contador[numbullet] = 0; 
              explosion[i].golbat[j].burst = 1;
              crobat[i].golbat[j].zubat[0].active = 1;
              crobat[i].golbat[j].zubat[1].active = 1;
             }
           }

             if(player.active  == 1)
           {
               if(COLLISION2(player, crobat[i], j) == 2)
              {
                col = 2;
               CLEAR_STATUS(crobat,i, j, k, col);
               Mix_PlayChannel(2, crygolbat, 0);
               Mix_PlayChannel(4, cryplayer, 0);
               pont += 20;
               explosion[i].golbat[j].burst = 1;
               crobat[i].golbat[j].zubat[0].active = 1;
               crobat[i].golbat[j].zubat[1].active = 1;
               player.active = 0;
               player.width = 0;
               player.height = 0;
               lives -= 1;
               direction = 0;
               tiro = 0;
               vel = 0;
               solta = 0;
               }
           }
}

if(!crobat[i].active && !crobat[i].golbat[j].active)
{
  if(tiro != 0 && COLLISION3(firebullet[numbullet], crobat[i], j, k) == 3 && ((firebullet[numbullet].dx != player.dx && firebullet[numbullet].dy != player.dy || firebullet[numbullet].dx == player.dx && firebullet[numbullet].dy != player.dy || firebullet[numbullet].dx != player.dx  && firebullet[numbullet].dy == player.dy)))
  {

       if(collision_on != 0)
       {
         collision_on = collision_on;
       }
        else{
          collision_on = 3;
        }

          if(collision_on == 3)
          {
            Mix_PlayChannel(3, cryzubat, 0);
            pont += 10;
          tiro = 0;
          fire[numbullet] = 0;
          contador[numbullet] = 0;
          contador_tiro = 0;
          explosion[i].golbat[j].zubat[k].burst = 1;
          CLEAR_STATUS(crobat, i,  j, k, collision_on);
      }
  }

  if(player.active  == 1)
{
  if(COLLISION3(player, crobat[i], j, k) == 3 )
{col = 3;
  CLEAR_STATUS(crobat,i, j, k, col);
  Mix_PlayChannel(3, cryzubat, 0);
  Mix_PlayChannel(4, cryplayer, 0);
  pont += 10;
  explosion[i].golbat[j].zubat[k].burst = 1;
  player.active = 0;
  player.width = 0;
  player.height = 0;
  lives -= 1;
  direction = 0;
  tiro = 0;
  vel = 0;
  solta = 0;
}
}

}

  
}
  }  
  collision_on = 0;
  col = 0;

}
}

}

void BLOW_UP()
{
        int i, j, k;

      for(i=0 ;i<4; i++)
   {

        if(explosion[i].burst == 1)
      {

         explosion[i].sy += 192;


         if(explosion[i].sy > 1536)
       {
          explosion[i].burst = 0;
         //explosion[i].sy = 0;
       }
         draw_playerrect(explosion[i], explosion_frame, screen);
      }

       else{
         explosion[i].dy = crobat[i].dy;
         explosion[i].dx = crobat[i].dx;
         explosion[i].sy = 0;
        }

          for(j=0; j<2; j++)
       {
          if(explosion[i].golbat[j].burst == 1)
       {

          explosion[i].golbat[j].sy += 192;


         if(explosion[i].golbat[j].sy > 3072)
         {
          explosion[i].golbat[j].burst = 0;
         //explosion[i].golbat[j].sy = 0;
         }

          draw_enemy2(explosion[i],j, explosion_frame, screen);
         }

      else{
            explosion[i].golbat[j].dy = crobat[i].golbat[j].dy;
            explosion[i].golbat[j].dx = crobat[i].golbat[j].dx;
            explosion[i].golbat[j].sy = 0;
           }

        for(k=0; k<2; k++)
        {
            if(explosion[i].golbat[j].zubat[k].burst == 1)
           {

             explosion[i].golbat[j].zubat[k].sy += 192;


              if(explosion[i].golbat[j].zubat[k].sy > 3072)
             {
               explosion[i].golbat[j].zubat[k].burst = 0;
                 //explosion[i].golbat[j].zubat[k].sy = 0;
              }

                  draw_enemy3(explosion[i],j,k, explosion_frame, screen);
             }

           else{
                 explosion[i].golbat[j].zubat[k].dy = crobat[i].golbat[j].zubat[k].dy;
                 explosion[i].golbat[j].zubat[k].dx = crobat[i].golbat[j].zubat[k].dx;
                 explosion[i].golbat[j].zubat[k].sy = 0;
                }
         }
     }
   }
}

void DOPLAYER_AGAIN()
{

  int i, j, k;

         if(player.active == 0)
       {
          revive += 1;
          tiro = 0;
          contador_tiro = 0;
          vel = 0;
          fire[0] = 0;
          contador[0] = 0;
          fire[1] = 0;
          contador[1] = 0;
          fire[2] = 0;
          contador[2] = 0;
          fire[3] = 0;
          contador[3] = 0;
          solta = 0;
          direction = 0;
          printf("%f\n", player.dy);

        if(revive == 30)
        {
          PLAYER_INFO();
          revive = 0;

          for(i=0; i<4; i++)
            {  for(j=0; j<2; j++)
                {   for(k=0; k<2; k++)
                        {
                          if(COLLISION3(player, crobat[i], j, k) != 3 || COLLISION2(player, crobat[i], j) != 2 || COLLISION(player, crobat[i]) != 1)
                          {
                            player.active = 1;
                          }

                          else{
                            revive = 0;
                          }
                        }
                      }
                    }
          
        }
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
             contador_tiro = 0;
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
               
              }

           }
}


void BULLETING(int i)
{

       

            if(fire[i] == 0)
           {
             firebullet[i].dx = player.dx;
             firebullet[i].dy = player.dy;
             contador[i] = 0;
           }

          if(fire[i]>0)
           {

                //firing = fire[i];
                firebullet[i].sx = FRAME_BULLET(fire[i]);
                firebullet[i].dx = DIRX(fire[i], firebullet[i], vel_tiro);
                firebullet[i].dy = DIRY(fire[i], firebullet[i], vel_tiro);
                contador[i]++;
                draw_playerrect(firebullet[i], movebullet, screen);
            
               if(contador[i]>=20)
              {
               fire[i] = 0;
               
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

              if(lives <= 0)
              {
                menu_op = 0;
                start_game = 0;
                pont = 0;
                fase1 = Mix_LoadMUS("sounds/menu.mp3");
                Mix_HaltMusic();    
              }

              else{
                    exit(0);
                  }
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

                                 if(fire[numtiro] != 0)
                                 {
                                  fire[numtiro] = fire[numtiro];
                                 }

                                 else{
                                  fire[numtiro] = (direction+1);
                                 }

                                if( numtiro <=3)
                                  {
                                   numtiro++;
                                  }

                                 if(numtiro >= 4 )
                                 {
                                  numtiro = 0;
                                 }

                               if(player.active == 1)
                               {
                                 Mix_PlayChannel(4, cryplayer, 0);
                               }
                                 break;
              

                case SDLK_RETURN: 

                if(typingname == 1)
                {
                  typingname = 0;
                  start_game = 0;
                  record.nome[initials] = '\0';
                  record.pontuacao = pont;
                  insere(&array, record);
                  fwrite(&array, sizeof(ARRAY), 1, p_arquivo);
                  
                  fclose(p_arquivo);
                  p_arquivo = fopen("recordes.bin", "rb");
                  

                  int clear;

                  for(clear =0; clear<initials; clear++)
                  {
                  record.nome[clear] = ' ';
                  }

                  initials = 0;

                  
                  character_screen = 1;

                  fase1 = Mix_LoadMUS("sounds/playerselect.mp3");
                Mix_HaltMusic(); 
                }
               
                  if(lives <= 0)
               {

                pont = 0;
                lives = 3;
                solta =0;
                vel = 0;
                Mix_HaltMusic();
                PLAYER_INFO();
               }
             Mix_PlayChannel(6, select_option, 0);
               break;


                while(name_typed == 0 && typingname == 1)
                {

                  if(initials < MAX_NOME)
                  {
                   case SDLK_a: record.nome[initials] = 'a';
                   Mix_PlayChannel(9, type_option, 0);
                initials++;
                ;break;
            case SDLK_b: record.nome[initials] = 'b';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_c: record.nome[initials] = 'c';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_d: record.nome[initials] = 'd';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_e: record.nome[initials] = 'e';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_f: record.nome[initials] = 'f';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_g: record.nome[initials] = 'g';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_h: record.nome[initials] = 'h';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_i: record.nome[initials] = 'i';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_j: record.nome[initials] = 'j';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_k: record.nome[initials] = 'k';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_l: record.nome[initials] = 'l';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_m: record.nome[initials] = 'm';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_n: record.nome[initials] = 'n';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_o: record.nome[initials] = 'o';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_p: record.nome[initials] = 'p';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_q: record.nome[initials] = 'q';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_r: record.nome[initials] = 'r';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_s: record.nome[initials] = 's';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_t: record.nome[initials] = 't';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_u: record.nome[initials] = 'u';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_v: record.nome[initials] = 'v';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_w: record.nome[initials] = 'w';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_x: record.nome[initials] = 'x';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_y: record.nome[initials] = 'y';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;
            case SDLK_z: record.nome[initials] = 'z';
            Mix_PlayChannel(9, type_option, 0);
                initials++; break;

               }

            case SDLK_BACKSPACE:
                  
                 initials--;
                 record.nome[initials] = ' ';

                 if(initials < 0)
                 {
                  initials = 0;
                 }
                 Mix_PlayChannel(10, delete_option, 0);
                 break;

                 if(initials >= MAX_NOME)
                 {
                  record.nome[12] = ' ';
                  initials = 11;
                 }

                


                }
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

                girar++;

                if(girar == 2)
                {
                    player.sx = FRAME_UPDATE_PLUS(player);
                    direction -= 1;;
                    if( direction < 0)
                   {
                        direction += 8;
                   }

                   girar = 0;
                 }

          }

          if(!rightright)
          {
                  girar++;

                  if(girar == 2)
                  {
                    player.sx = FRAME_UPDATE_MINUS(player);
                    direction += 1;
                    if( direction > 7)
                   {
                     direction -= 8;
                   }

                   girar = 0;
                 }
          }
}

void ENEMY_POSITION()
{

    int i, j, k;



    for(i=0; i<4; i++)

    {   
         crobat[i].golbat[0].sy += 192;
         crobat[i].golbat[1].sy += 192;

      for(j=0; j<2; j++)
        { 
          crobat[i].golbat[j].zubat[0].sy += 192;
          crobat[i].golbat[j].zubat[1].sy = crobat[i].golbat[j].zubat[0].sy;
         if(crobat[i].active)
       {
         //UPDATE_LOCATION();
        crobat[i].golbat[j].dx = 20 + crobat[i].dx ;
        crobat[i].golbat[j].dy = 20 + crobat[i].dy ;
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

       if(crobat[i].golbat[j].active == 1)
       {
         ASTEROIDS_ON2(i);
        crobat[i].golbat[j].zubat[0].dx = 30 + crobat[i].golbat[j].dx ;
        crobat[i].golbat[j].zubat[0].dy = 30 + crobat[i].golbat[j].dy ;
        crobat[i].golbat[j].zubat[1].dx = 30 + crobat[i].golbat[j].dx ;
        crobat[i].golbat[j].zubat[1].dy = 30 + crobat[i].golbat[j].dy ;

       }


        if(crobat[i].golbat[j].zubat[0].active == 1 || crobat[i].golbat[j].zubat[1].active == 1) //|| //crobat[i].golbat[j].zubat[1].active == 1)
        {

          ASTEROIDS_ON1(i, j);
        }

     
        
    }

  }

}

void PLAYER_DEAD()
{
                  if(lives <= 0)
         {

          player.active = 0;
          Mix_PauseMusic();
          int i, j, k;

         while(all_enemies > 0)
         {
          for(i=0; i<4; i++)
          { 

            for(j=0; j<2; j++)
            {


             for(k=0; k<2; k++)
              {


               if(crobat[i].active)
               {
                CLEAR_STATUS(crobat, i, j, k, 1);
                explosion[i].burst = 0;
                crobat[i].golbat[0].active = 1;
                crobat[i].golbat[1].active = 1;

                //delete -=1;

                }
                if(crobat[i].golbat[j].active)
                {
                CLEAR_STATUS(crobat, i, j, k, 2);
                explosion[i].golbat[j].burst = 0;
                crobat[i].golbat[j].zubat[0].active = 1;
                crobat[i].golbat[j].zubat[1].active = 1;
                //delete -= 1;
                }

                if(crobat[i].golbat[j].zubat[k].active)
                {
                CLEAR_STATUS(crobat, i, j, k, 3);
                explosion[i].golbat[j].zubat[k].burst = 0;
                //delete -= 1;
              }
              

              }
            }

          }
        }
          typingname = 1;
          direction = 0;
          vel = 0;
          solta = 0;
          upup = 1;
          tiro =0;
          contador_tiro = 0;
          fire[0] = 0;
          contador[0] = 0;
          fire[1] = 0;
          contador[1] = 0;
          fire[2] = 0;
          contador[2] = 0;
          fire[3] = 0;
          contador[3] = 0;
          speedgolbat = 1.16;
          speedzubat = 1.25;
          Mix_HaltChannel(5);

          //menu_op = 0;
          
          apply_surface(0, 0, continuegame, screen);
          ENTER_NAME();
          
          //lives = 0;
         }

}

void SCORE()
{
  itoa(pont, ponts);

  record.pontuacao = pont;

       draw_text(ponts, fonte, screen, 400, 0, 160, 32, 240);
       draw_text(ponts, fonte_solid, screen, 400, 0, 255, 255, 255);
       draw_text("Score : ", fonte, screen, 280, 0, 0, 0, 255);
       draw_text("Score : ", fonte_solid, screen, 280, 0, 255, 255, 0);
       itoa(all_enemies, enemies_rest);
       itoa(lives, lifebar);
       //draw_text("Vidas : ", fonte, screen, 630, 0, 0, 0, 255);
       //draw_text("Vidas : ", fonte_solid, screen, 630, 0, 255, 255, 0);
       apply_surface(630, 5, lifeimg, screen);


       draw_text("x", fonte, screen, 670, 20, 160, 32, 240);
       draw_text("x", fonte_solid, screen, 670, 20, 255, 255, 255);

       draw_text(lifebar, fonte, screen, 700, 20, 160, 32, 240);
       draw_text(lifebar, fonte_solid, screen, 700, 20, 255, 255, 255);
}

void PLAYING_MUSIC()
{
              if(Mix_PlayingMusic() == 0)
       {
        musicloop--;
        Mix_PlayMusic(fase1, 0);
        Mix_RewindMusic();

        if(musicloop <=0)
        {
           musicloop = 10;
        }


       }
}
void CLEAN_UP()
{
SDL_FreeSurface(intro);
SDL_FreeSurface(icon);
SDL_FreeSurface(hero);
SDL_FreeSurface(explosion_frame);
SDL_FreeSurface(lifeimg);
SDL_FreeSurface(soundoff);
SDL_FreeSurface(logo);
SDL_FreeSurface(enemy1right);
SDL_FreeSurface(enemy1left);
SDL_FreeSurface(enemy2right);
SDL_FreeSurface(enemy2left);
SDL_FreeSurface(enemy3);
SDL_FreeSurface(enemy3left);
SDL_FreeSurface(movebullet);
SDL_FreeSurface(background);
Mix_FreeMusic(fase1);
Mix_FreeChunk(cryplayer);
Mix_FreeChunk(crycrobat);
Mix_FreeChunk(crygolbat);
Mix_FreeChunk(cryzubat);
Mix_FreeChunk(select_option);
Mix_FreeChunk(choose_option);
Mix_FreeChunk(back_option);
Mix_FreeChunk(lowhp);
Mix_FreeChunk(type_option);
Mix_FreeChunk(delete_option);
fclose(p_arquivo);

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
       speedgolbat += 0.20;
       speedzubat += 0.50;
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

void bubble_sort(RECORDE list[], int n)
{
  int i, j;
    RECORDE swap;

  for(i = 0 ; i < ( n - 1 ); i++)
  {
    for(j = 0 ; j < n - i - 1; j++)
    {
      if(list[j].pontuacao < list[j+1].pontuacao)
      { 
        swap = list[j];
        list[j] = list[j+1];
        list[j+1] = swap;
      }
    }
  }
}

void sort(ARRAY *array)
{
  bubble_sort(array->vetor, array->n);
}

RECORDE elemento(ARRAY *array, int posicao)
{
  return array->vetor[posicao];
}

int tamanho(ARRAY *array)
{
  return array->n;
}

void remove_posicao(ARRAY *array, int posicao)
{
  if(tamanho(array) == 0)
  {
    return;
  }
  else if(tamanho(array) == 1)
  {
    array->n -= 1;
    return;
  }
  else
  {
    array->n -= 1;
    array->vetor[posicao] = array->vetor[tamanho(array)];
  }
    
    sort(array);
}

void insere(ARRAY *array, RECORDE recorde)
{
    if(tamanho(array) < MAX_ARRAY)
    {
        array->vetor[tamanho(array)] = recorde;
        array->n += 1;
    }
    else
    {
        RECORDE menor_recorde;
        menor_recorde = elemento(array, MAX_ARRAY - 1);
        
        if(menor_recorde.pontuacao >= recorde.pontuacao)
        {
            return;
        }
        else
        {
            remove_posicao(array, MAX_ARRAY - 1);
            insere(array, recorde);
            return;
        }
    }
    
    sort(array);
}

void imprime(ARRAY *array)
{
  int i;

    printf("------------------------------\n");
  printf("Recordes:\n");

  RECORDE recorde;

   //int x = 50, y = 50;

  for(i = 0; i < tamanho(array); i++)
  {
        recorde = elemento(array, i);
        printf("%d - %d :: %s \n", i+1, recorde.pontuacao, recorde.nome);
  }

  printf("------------------------------\n");
}

void ENTER_NAME()
{

       fclose(p_arquivo);
       p_arquivo = fopen("recordes.bin", "wb");
       printf("Nome do Recordista:");

       draw_text("GAME OVER!", fonte, screen, 350, 0, 0, 0, 255);
       draw_text("GAME OVER!", fonte_solid, screen, 350, 0, 255, 255, 255);

       draw_text("Input your name : ", fonte, screen, 10, HEIGHT/2, 0, 0, 255);
       draw_text("Input your name : ", fonte_solid, screen, 10, HEIGHT/2, 255, 255, 255);
       draw_text(record.nome, fonte_solid, screen, 250, HEIGHT/2, 255, 255, 255);
       draw_text(record.nome, fonte, screen, 250, HEIGHT/2, 0, 0, 255);
       printf("pontos %d", pont);
    
}

void RANKING()
{

    int i, x= 150, y=50;
    
   


    if(fopen("recordes.bin", "rb") != NULL)
    {
      fread(&arraynew, sizeof(ARRAY), 1, p_arquivo);
            for(i=0; i<10; i++)
           {
            

            if(arraynew.vetor[i].pontuacao != 0)
            {
            itoa((i+1), pontsrec);
            draw_text(pontsrec, fonte, screen, 0, y, 0, 0, 255);
            draw_text(pontsrec, fonte_solid, screen, 0, y, 255, 255, 255);
            draw_text(" -", fonte, screen, 18, y, 0, 0, 255);
            draw_text(" -", fonte_solid, screen, 18, y, 255, 255, 255);

            draw_text(arraynew.vetor[i].nome, fonte, screen, 50, y, 0, 0, 255);
            draw_text(arraynew.vetor[i].nome, fonte_solid, screen, 50, y, 255, 255, 255);
            itoa(arraynew.vetor[i].pontuacao, pontsrec );
            draw_text(pontsrec, fonte, screen, x+30, y, 0, 0, 255);
            draw_text(pontsrec, fonte_solid, screen, x+30, y, 255, 255, 255);
            y+= 50;
            }

            if(arraynew.vetor[0].pontuacao == 0)
            {
              draw_text("Sem Recordes", fonte, screen, 50, y, 0, 0, 255);
              draw_text("Sem Recordes", fonte_solid, screen, 50, y, 255, 255, 255);
            }
           }
     }
 

 else{
       draw_text("No scores!", fonte, screen, x, 70, 0, 0, 255);
       draw_text("No scores!", fonte_solid, screen, x, 70, 255, 215, 0);     
     }

 y = 0;
        



    imprime(&arraynew);

    fclose(p_arquivo);
}

void QUITTING()
{
  fclose(p_arquivo);
  TTF_Quit();
  Mix_CloseAudio();
  SDL_Quit();
}


int main(int argc, char** args)
{

     SETUP_INIT();
     EXPLOSION_INFO();
     Mix_AllocateChannels(11);
     Mix_VolumeMusic(128);
     Mix_Volume(1, 128);
     Mix_Volume(2, 128);
     Mix_Volume(3, 128);
     Mix_Volume(4, 128);

     int x = 50;
     int y = 50;

    Uint32 start;

    while(gamerunning)
{ 
     start = SDL_GetTicks();

       if(start_game)
    {  apply_surface ( 0, 0, background, screen );
       

       SCORE();




       DOPLAYER_AGAIN();
       BLOW_UP();
       if(lives > 0)
       {
              ENEMIES_DEAD();
        }


       int zeta;

       for(zeta= 0; zeta<4; zeta++)
       {
       BULLETING(zeta);
       }
       DECELERATION();
       CHECK_COLISION();
       KEYSTATE();
       draw_playerrect(player, hero, screen);
       PLAYER_DEAD();

             if(lives == 2)
      {
        Mix_PlayChannel(5, lowhp, 0);
      }

       }




else{

         MENU_KEYSTATE();
         MENU_IMAGES();
         if(character_screen == 1)
{
  SDL_FreeSurface(menu);
  CHOOSE_PLAYER();
  player.dx = 70;
  player.dy = 280;
  draw_playerrect(player, hero, screen);

}
 draw_player(0, 0, 200, 0, 400, 113, logo, screen);

  draw_text("Created by Wesley Muniz", fontesmall2, screen, 400, 50, 255, 255, 255);
     draw_text("Created by Wesley Muniz", fontesmall, screen, 408, 50, 0, 0, 0);
   if(instructions == 1)
   {
    menu_op = 3;
    menu = IMG_Load("backgrounds/instructions.jpg");
    apply_surface(0, 0, menu, screen);
   }

   if(ranking == 1)
   {
    menu_op = 1;
    apply_surface(0, 0, highscore, screen);
    draw_text("High Scores", fonte, screen, 300, 0, 0, 0, 255);
    draw_text("High Scores", fonte_solid, screen, 300, 0, 255, 215, 0);
     RANKING();
     
   }

    if(volume_on >= 1)
    {
      apply_surface(710, 0, soundoff, screen);
    }
    
   }

   //PLAYER_DEAD();
   PLAYING_MUSIC();



        
  if(1000/FPS >(SDL_GetTicks()-start))
          SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
       SDL_Flip( screen);
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