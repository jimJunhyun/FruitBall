#pragma once

class Object;
class ForceManager
{
	SINGLE(ForceManager);

public:

	void Init();
	void Update();

	void AddForcedGroups(OBJECT_GROUP group);
	void RemoveForcedGroups(OBJECT_GROUP group);

	void SetFloorRes(float val) { floorResistance = val; }
	const float& GetFloorRes() const { return floorResistance; }

	const float GRAVITY = 980.0f;

private:
	std::set<OBJECT_GROUP> forcedGroups;

	float floorResistance;
};

