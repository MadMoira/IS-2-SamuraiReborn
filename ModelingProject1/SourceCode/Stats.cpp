
#include "Stats.h"
#include "GameRender.h"

PlayerStats::Health::Health(Vector2f lifeQPos, Vector2f lifeQOff, Vector2f lifeIPos, Vector2f lifeIOff)
{
  lifeQuadPosition = lifeQPos;
  lifeQuadOffset = lifeQOff;
  lifeInitialPosition = lifeIPos;
  lifeInitialOffset = lifeIOff;
}

PlayerStats::Stats::Stats(void)
{
  Vector2f lifeIPos(0.0f, 0.0f); //Coordinates X-Y First Quad Of The Health Bar
  Vector2f lifeIOff(19.53f, 10.53f); //Width And Height Of The First Quad Of The Health Bar
  Vector2f lifeQPos(2.3f, 13.97f); //Coordinates X-Y Common Quad Of The Health Bar
  Vector2f lifeQOff(7.00f, 10.53f); //Width And Height Of The Common Quad Of The Health Bar

  health = PlayerStats::Health(lifeQPos, lifeQOff, lifeIPos, lifeIOff);

  health.pointsOfLife = 2800;
  health.healthBar = new Image::GameImage(Vector2f(10.0f, 10.0f), //X-Y Position Of The Health Bar
                                      Vector2f(353.33f, 145.0f), //Width And Height Of The Health Bar
                                      Vector2f(20.58f, 0.0f), //Texture Position X-Y Of The Health Bar
                                      "Resources/UI/HealthBar.png");
}

PlayerStats::Stats::~Stats(void)
{	
}

void PlayerStats::Stats::drawHealthBar()
{
  GLfloat widthTexture, heightTexture;

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_TEXTURE_COORD_ARRAY );	

  glBindTexture( GL_TEXTURE_2D, health.healthBar->getTexture() );

  glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &widthTexture);
  glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &heightTexture);

  Vector2f position = health.healthBar->getPosition();
  Vector2f offset = health.healthBar->getOffset();
  Vector2f texturePosition = health.healthBar->getTexturePosition();

  const GLfloat vertX = position.x;
  const GLfloat vertY = position.y;
  const GLfloat vertOffsetX = offset.x;
  const GLfloat vertOffsetY = offset.y;
    
  const GLfloat verts[] = {
            vertX, vertY,
            vertX + vertOffsetX, vertY,
            vertX + vertOffsetX, vertY + vertOffsetY,
            vertX, vertY + vertOffsetY
  };

  const GLfloat textureX = texturePosition.x / widthTexture;
  const GLfloat textureY = texturePosition.y / heightTexture;
  const GLfloat textureWidth = offset.x / widthTexture;
  const GLfloat textureHeight = offset.y / heightTexture;

  const GLfloat texVerts[] = {
            textureX, textureY,
            textureX + textureWidth, textureY,
            textureX + textureWidth, textureY + textureHeight,
            textureX, textureY + textureHeight
  };
            
  glVertexPointer(2, GL_FLOAT, 0, verts);
  glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
  glDrawArrays(GL_QUADS, 0, 4);

  glDisableClientState( GL_VERTEX_ARRAY );			
  glDisableClientState( GL_TEXTURE_COORD_ARRAY );	
}

void PlayerStats::Stats::drawHealth()
{
  GLfloat widthTexture, heightTexture;

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
  glEnableClientState( GL_VERTEX_ARRAY );
  glEnableClientState( GL_TEXTURE_COORD_ARRAY );	

  glBindTexture( GL_TEXTURE_2D, health.healthBar->getTexture() );

  glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &widthTexture);
  glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &heightTexture);

  Vector2f initial(131.25f + health.healthBar->getPosition().x, 
                   52.0f + health.healthBar->getPosition().y);

  for (int i = health.pointsOfLife/100; i >= -1; i--)
  {
    GLfloat vertX = initial.x + i*health.lifeQuadOffset.x;
    GLfloat vertY = initial.y;
    GLfloat vertOffsetX = health.lifeQuadOffset.x;
    GLfloat vertOffsetY = health.lifeQuadOffset.y;

    GLfloat textureX = health.lifeQuadPosition.x / widthTexture;
    GLfloat textureY = health.lifeQuadPosition.y / heightTexture;
    GLfloat textureWidth = health.lifeQuadOffset.x / widthTexture;
    GLfloat textureHeight = health.lifeQuadOffset.y / heightTexture;

    if ( i == -1 )
    {
      initial.x = 111.0f + health.healthBar->getPosition().x;
      vertX = initial.x;
      vertOffsetX = health.lifeInitialOffset.x;
      vertOffsetY = health.lifeInitialOffset.y;

      textureX = health.lifeInitialPosition.x / widthTexture;
      textureY = health.lifeInitialPosition.y / heightTexture;
      textureWidth = health.lifeInitialOffset.x / widthTexture;
      textureHeight = health.lifeInitialOffset.y / heightTexture;
    }

    const GLfloat verts[] = {
            vertX, vertY,
            vertX + vertOffsetX, vertY,
            vertX + vertOffsetX, vertY + vertOffsetY,
            vertX, vertY + vertOffsetY
    };

    const GLfloat texVerts[] = {
            textureX, textureY,
            textureX + textureWidth, textureY,
            textureX + textureWidth, textureY +textureHeight,
            textureX, textureY + textureHeight
    };
            
    glVertexPointer(2, GL_FLOAT, 0, verts);
    glTexCoordPointer(2, GL_FLOAT, 0, texVerts);
    glDrawArrays(GL_QUADS, 0, 4);
  }

  glDisableClientState( GL_VERTEX_ARRAY );			
  glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}