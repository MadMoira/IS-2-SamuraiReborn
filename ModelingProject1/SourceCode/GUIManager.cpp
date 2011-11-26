
#include "GUIManager.h"
#include "GameRender.h"

RPRGUI::GUIManager::GUIManager(void)
{
}

RPRGUI::GUIManager::~GUIManager(void)
{
}

RPRGUI::PushButton* RPRGUI::GUIManager::createButton(MenuData::MainMenuOptions id, Vector2f pos, Vector2f dimensions, 
                                                     Vector2f posTexture, int idChangeState)
{
  PushButton* newButton = new RPRGUI::PushButton(id, pos, dimensions, posTexture);
  newButton->setIdChangeState(idChangeState);
  return newButton;
}

Image::GameImage* RPRGUI::GUIManager::createStaticImage(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, 
                                                       std::string filename)
{
  return new Image::GameImage(imagePosition, imageOffset, texturePosition, filename);
}