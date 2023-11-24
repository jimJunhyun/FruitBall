#include "pch.h"
#include "ForceManager.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Object.h"

void ForceManager::Init()
{

}

void ForceManager::Update()
{
	for (std::set<OBJECT_GROUP>::iterator iter = forcedGroups.begin(); iter != forcedGroups.end(); iter++)
	{
		std::shared_ptr<Scene> curScene = SceneMgr::GetInst()->GetCurScene();
		const vector<Object*> selectedGroups = curScene->GetGroupObject(*iter);
		
		for (UINT i = 0; i < selectedGroups.size(); ++i)
		{
			Vec2 curObjVel = selectedGroups[i]->GetVelocity();
			if (curObjVel.Length() == 0) {
				continue;
			}
			
			curObjVel = curObjVel - (-curObjVel.Normalize()) * (curObjVel.Length() * floorResistance);
			selectedGroups[i]->SetVelocity(curObjVel);
		}
	}
}

void ForceManager::AddForcedGroups(OBJECT_GROUP group)
{
	forcedGroups.insert(group);
}

void ForceManager::RemoveForcedGroups(OBJECT_GROUP group)
{
	if (forcedGroups.find(group) != forcedGroups.end()) {
		forcedGroups.erase(forcedGroups.find(group));
	}
}
