#include "globalStuff.h"
#include "BehaviourManager.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "SeekAndFleeBehaviour.h"
#include "ApproachBehaviour.h"
#include "PursueAndEvadeBehaviour.h"
#include "WanderBehaviour.h"

// These are for the transformation glm stuff
#include <glm/glm.hpp> 
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
cMeshObject* pDebugSphere;
std::vector <cMeshObject*> vec_Enemies;

void InitGame() {
	behavManager = new BehaviourManager();

	cMeshObject* pPlayer = findObjectByFriendlyName("player");
	cMeshObject* pApproachEnemy = findObjectByFriendlyName("enemy");
	vec_Enemies.push_back(pApproachEnemy);
	cMeshObject* pWanderEnemy = findObjectByFriendlyName("wanderEnemy");
	vec_Enemies.push_back(pWanderEnemy);
	cMeshObject* pPuruseEnemy = findObjectByFriendlyName("puruseEnemy");
	vec_Enemies.push_back(pPuruseEnemy);
	cMeshObject* pSeekEnemy = findObjectByFriendlyName("seekEnemy");
	vec_Enemies.push_back(pSeekEnemy);
	pDebugSphere = findObjectByFriendlyName("DebugSphere");

	pPlayer->initPos = pPlayer->position;
	pApproachEnemy->initPos = pApproachEnemy->position;
	pWanderEnemy->initPos = pWanderEnemy->position;
	pPuruseEnemy->initPos = pPuruseEnemy->position;
	pSeekEnemy->initPos = pSeekEnemy->position;

	ApproachBehaviour* approach = new ApproachBehaviour(pApproachEnemy, pPlayer, 25.2f, 14.2f);
	behavManager->SetBehaviour(pApproachEnemy, approach);
	WanderBehaviour* wander = new WanderBehaviour(pWanderEnemy, 22.2f, 10.2f, 0.0f, glm::vec3(0.0f), 30.0f, -30.0f);
    behavManager->SetBehaviour(pWanderEnemy, wander);
	PursueAndEvadeBehaviour* PursueAndEvade = new PursueAndEvadeBehaviour(pPuruseEnemy, pPlayer, 28.2f, 10.2f);
	behavManager->SetBehaviour(pPuruseEnemy, PursueAndEvade);
	SeekAndFleeBehaviour* seekAndFlee = new SeekAndFleeBehaviour(pSeekEnemy, pPlayer, 24.2f, 10.0f, 5.0f, 45.0f, 60.0f);
	behavManager->SetBehaviour(pSeekEnemy, seekAndFlee);
	//FleeBehaviour* flee = new FleeBehaviour(pEnemy, pPlayer, 7.2f, 4.2f);
	//behavManager->SetBehaviour(pEnemy, flee);
	
}

void PlayerColTest(double deltaTime, GLuint shaderProgramID)
{
	cMeshObject* pPlayer = findObjectByFriendlyName("player");
	cMeshObject* pEnemy = findObjectByFriendlyName("enemy");
	behavManager->update(deltaTime);

	//draw Debug Info
	for (int i = 0; i < vec_pObjectsToDraw.size(); i++)
	{
		if (vec_pObjectsToDraw[i]->shapeType == cMeshObject::SPHERE)
		{
			if(vec_pObjectsToDraw[i]->bIsVisible)
			{
				sSphere* sphere = (sSphere*)(vec_pObjectsToDraw[i]->pTheShape);
				pDebugSphere->position = vec_pObjectsToDraw[i]->position;
				pDebugSphere->setUniformScale(sphere->radius);
				pDebugSphere->setDiffuseColour(glm::vec3(0.0f, 1.0f, 0.0f));
				glm::mat4 matIdentity = glm::mat4(1.0f);
				DrawObject(pDebugSphere, matIdentity, program);
			}
			//pDebugSphere->bIsVisible = false;
		}
	}
	//cMeshObject* pDebugSphereLeft = findObjectByFriendlyName("DebugSphereLeft");
	//cMeshObject* pDebugSphereRight = findObjectByFriendlyName("DebugSphereRight");
	//cMeshObject* pDebugSphereNose = findObjectByFriendlyName("DebugSphereNose");

	
		//pPlayer->setMeshOrientationEulerAngles(glm::vec3(camera.Front.y/10, cameraFront.x/10, 0.0f), false);
		//pPlayer->adjMeshOrientationEulerAngles(glm::vec3(-0.005f, 0.0f, 0.0f), false);
		//pPlayer->setMeshOrientationEulerAngles(glm::vec3(0.0f, camera.Front.x, 0.0f), false);
		//pPlayer->adjMeshOrientationEulerAngles(glm::vec3(0.0, -0.005f, 0.0f), false); 
   //DELETE LASER BEAMS


	glm::vec4 vecForwardDirection_ModelSpace = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	glm::quat qPlayer29Rotation = pPlayer->getQOrientation();
	glm::mat4 matQPlayer29rotation = glm::mat4(qPlayer29Rotation);
	glm::vec4 vecForwardDirection_WorldSpace = matQPlayer29rotation * vecForwardDirection_ModelSpace;
	vecForwardDirection_WorldSpace = glm::normalize(vecForwardDirection_WorldSpace);
	float forwardSpeed = 20.5f;
	float forwardSpeedThisFrame = forwardSpeed * deltaTime;
	pPlayer->velocity = vecForwardDirection_WorldSpace * forwardSpeed;
	


	glm::vec4 noseContactPoint_ModelSpace = glm::vec4(0.0f, 0.0f, 2.4705f, 1.0f);
	glm::vec4 leftWingTipContactPoint_ModelSpace = glm::vec4(1.8692f, 0.0f, -1.5f, 1.0f);
	glm::vec4 rightWingTipContactPoint_ModelSpace = glm::vec4(-1.8692f, 0.0f, -1.5f, 1.0f);

	glm::mat4 matTransform = glm::mat4(1.0f);
	glm::mat4 matTranslation = glm::translate(glm::mat4(1.0f),
		pPlayer->position);

	
	//pPlayerSpheres->position = pPlayer->position;
	//matTransform = matTransform * matTranslation;
	//glm::quat qRotation = pPlayer->getQOrientation();
	//glm::mat4 matQrotation = glm::mat4(qRotation);
	//matTransform = matTransform * matQrotation;

	//glm::vec4 noseContactPoint_WorldSpace = glm::vec4(0.0f);
	//glm::vec4 leftWingTipContactPoint_WorldSpace = glm::vec4(0.0f);
	//glm::vec4 rightWingTipContactPoint_WorldSpace = glm::vec4(0.0f);
	//
	//noseContactPoint_WorldSpace = matTransform * noseContactPoint_ModelSpace;
	//leftWingTipContactPoint_WorldSpace = matTransform * leftWingTipContactPoint_ModelSpace;
	//rightWingTipContactPoint_WorldSpace = matTransform * rightWingTipContactPoint_ModelSpace;


	//glm::mat4 matIdentity = glm::mat4(1.0f);

	// nose:
	//pDebugSphereNose->position = noseContactPoint_WorldSpace;
	//left wing point:
	//pDebugSphereLeft->position = leftWingTipContactPoint_WorldSpace;
	//Right wing point
	//pDebugSphereRight->position = rightWingTipContactPoint_WorldSpace;
	//LightManager->vecLights.at(7)->position = glm::vec4(noseContactPoint_WorldSpace);
	//LightManager->vecLights.at(7)->SetRelativeDirection(glm::normalize(pPlayer->velocity));

	//increase timer if enemy is "dead"
	for (int i = 0; i < vec_Enemies.size(); i++)
	{
		if (!vec_Enemies[i]->bIsVisible)
		{
			vec_Enemies[i]->time_dead += (float)deltaTime;
			if (vec_Enemies[i]->time_dead > 4.0f)
			{
				vec_Enemies[i]->position = vec_Enemies[i]->initPos;
				vec_Enemies[i]->bIsUpdatedByPhysics = true;
				vec_Enemies[i]->bIsVisible = true;

				vec_Enemies[i]->time_dead = 0.0f;
			}
		}

	}


	
	for (int i = 0; i < vec_pObjectsToDraw.size(); i++)
	{
		if (vec_pObjectsToDraw[i]->friendlyName == "beam")
		{
			if (glm::distance(vec_pObjectsToDraw[i]->initPos, vec_pObjectsToDraw[i]->position) > 300.0f)
			{
				//vec_pObjectsToDraw[i].
				delete vec_pObjectsToDraw[i];
				vec_pObjectsToDraw.erase(vec_pObjectsToDraw.begin() + i);
			}
		}
	}



	////Respawn Dead Enemies
	//for (int i; i < vec_Enemies.size(); i++)
	//{
	//	mTimeWaitedSoFar += (float)dt;
	//	if (mTimeWaitedSoFar > mTimeToWait)
	//	{
	//		mCurTarget = glm::vec3(mRelPos.x + RandomFloat(mDwnLim, mUpLim), 0.0f, mRelPos.z + RandomFloat(mDwnLim, mUpLim));
	//		mStart = true;
	//	}
	//	//Ressurect!
	//}

	return;
}