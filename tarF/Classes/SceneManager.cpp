#include "SceneManager.h"
#include "TowerPosEditorScene.h"
#include "TollgateScene.h"

SceneManager* SceneManager::mSceneManager = NULL;

SceneManager* SceneManager::getInstance() {
    if(mSceneManager == NULL) {
        mSceneManager = new SceneManager();
        if(mSceneManager && mSceneManager->init()) {
            mSceneManager->autorelease();
            mSceneManager->retain();
        }
        else {
            CC_SAFE_DELETE(mSceneManager);
            mSceneManager = NULL;
        }
    }

    return mSceneManager;
}

bool SceneManager::init() {

    return true;
}

void SceneManager::changeScene( EnumSceneType enScenType ) {
    Scene* pScene = NULL;

    switch (enScenType) {
    case en_TollgateScene: /* 关卡场景 */
		pScene = TollgateScene::createScene();
        break;
    case en_TollgateEditorScene:    /* 关卡编辑器场景 */
        pScene = TowerPosEditorScene::createScene();
        break;
	case en_WinScene:		/* 胜利场景 */
		break;
	case en_GameOverScene:	/* 游戏结束场景 */
		break;
    }

    if(pScene == NULL) {
        return;
    }

    Director* pDirector = Director::getInstance();
    Scene* curScene = pDirector->getRunningScene();
    if(curScene == NULL) {
        pDirector->runWithScene(pScene);
    }
    else {
        pDirector->replaceScene(pScene);
    }
}
