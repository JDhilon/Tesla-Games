#include "Track.h"

Track::Track() {}
Track::~Track() {}
void Track::addPointToList(float x, float y, float z, int action) {
	this->listOfPoints.push_back(std::make_unique<TrackDrivingPoint>(x, y, z, action));
}

void Track::performMove(Vehicle* v) {
	TrackDrivingPoint* pastTarget = &v->pastTarget;
	TrackDrivingPoint* currentTarget = &v->curTarget;

	int pastAction = pastTarget->actionToTake;
	int currentAction = currentTarget->actionToTake;

	PxU32 curGear = v->gVehicle4W->mDriveDynData.getCurrentGear();
	float angleToTurn = getAngleToTurnBy(currentTarget, v);

	//The method names themselves tell you for what combinations the method is for
	if (pastAction == trackDrivingPointActions::START && currentAction == trackDrivingPointActions::SLOW_DOWN) {
		//The code for the initial 
		this->pastStartCurrentSlowdown(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::TURN_EXIT && currentAction == trackDrivingPointActions::SLOW_DOWN) {
	}

	//******************************************************************************************************************
	//**************************************** TURNING STUFF ***********************************************************
	//******************************************************************************************************************
	else if (pastAction == trackDrivingPointActions::SLOW_DOWN && currentAction == trackDrivingPointActions::TURN_IN) {
		//Slow down before entering the turn
		this->pastSlowDownCurrentTurnIn(curGear, angleToTurn, v);
	}

	//This is for normal turns or short U turn style
	else if (pastAction == trackDrivingPointActions::TURN_IN && currentAction == trackDrivingPointActions::APEX_MAJOR) {
		//Hit the apex (midpoint, kinda) of the turn
		this->pastTurnInCurrentMajor(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::APEX_MAJOR && currentAction == trackDrivingPointActions::TURN_EXIT) {
		//Reach the exit point of the turn
		this->pastMajorCurrentExit(curGear, angleToTurn, v);
	}

	//This is for long U turn style turns (two minors one major)
	else if (pastAction == trackDrivingPointActions::TURN_IN && currentAction == trackDrivingPointActions::APEX_MINOR) {
		//First apex of the turn
		this->pastTurnInCurrentMinor(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::APEX_MINOR && currentAction == trackDrivingPointActions::APEX_MAJOR) {
		//Imaginary Apex of turn (help co-ordinate Ai position in case of spinouts)
		this->pastMinorCurrentMajor(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::APEX_MAJOR && currentAction == trackDrivingPointActions::APEX_MINOR) {
		//second (third) apex of the turn
		this->pastMajorCurrentMinor(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::APEX_MINOR && currentAction == trackDrivingPointActions::TURN_EXIT) {
		//Reach exit point of turn
		this->pastMinorCurrentExit(curGear, angleToTurn, v);
	}

	else {
		v->forwards(0.f);
		v->reverse(1.f);
		v->turn(0.f);
	}

	
}

/*
I AM WELL AWARE THESE METHODS CONTAIN DUPLICATED CODE, HOWEVER IT IS TO ALLOW FOR EASY FINE TUNING OF THE TURN MECHANICS
*/

void Track::pastStartCurrentSlowdown(PxU32 curGear, float angleToTurn, Vehicle* v) {
	if (std::abs(angleToTurn) < 5.f) {
		v->turn(0.f);
		v->forwards(1.f);
		v->reverse(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.2f);
				}
				else {
					v->turn(0.2f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.4f);
				}
				else {
					v->turn(0.4f);
				}
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.4f);
				}
				else {
					v->turn(0.4f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.6f);
				}
				else {
					v->turn(0.6f);
				}
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.6f);
				}
				else {
					v->turn(0.6f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.8f);
				}
				else {
					v->turn(0.8f);
				}
			}
		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.5f);
			if (curGear <= PxVehicleGearsData::eTHIRD) {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-0.8f);
				}
				else {
					v->turn(0.8f);
				}
			}
			else {
				if (angleToTurn < 0) {
					//turn left
					v->turn(-1.f);
				}
				else {
					v->turn(1.f);
				}
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());

			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					v->turn(-1.f);
				}
				else {
					v->turn(1.f);
				}
			}
		}
	}
}

void Track::pastSlowDownCurrentTurnIn(PxU32 curGear, float angleToTurn, Vehicle* v) {
	if (curGear > PxVehicleGearsData::eSECOND) {
		if (std::abs(angleToTurn) < 5.f) {
			v->turn(0.f);
			v->forwards(0.f);
			v->reverse(1.f);
		}
		else {
			if (angleToTurn < 0) {
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
			v->reverse(1.f);
			v->forwards(0.f);
		}
	}
	else {
		if (std::abs(angleToTurn) < 5.f) {
			v->turn(0.f);
			v->forwards(0.4f);
			v->reverse(0.f);
		}
		else {
			if (angleToTurn < 0) {
				v->turn(-0.7f);
			}
			else {
				v->turn(0.7f);
			}
			v->reverse(0.f);
			v->forwards(0.3f);
		}
	}
}

void Track::pastTurnInCurrentMajor(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eSECOND;
	if (curGear > maxGearAllowed) {
		v->reverse(0.4f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.65f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.65f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.65f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.65f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					v->turn(-1.f);
				}
				else {
					v->turn(1.f);
				}
			}
		}
	}
}
void Track::pastMajorCurrentExit(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eFIFTH;
	if (curGear > maxGearAllowed) {
		v->reverse(0.f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					v->turn(-1.f);
				}
				else {
					v->turn(1.f);
				}
			}
		}
	}
}


void Track::pastTurnInCurrentMinor(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eTHIRD;
	if (curGear > maxGearAllowed) {
		v->reverse(0.4f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					v->turn(-1.f);
				}
				else {
					v->turn(1.f);
				}
			}
		}
	}
	
}
void Track::pastMinorCurrentMajor(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eFOURTH;
	if (curGear > maxGearAllowed) {
		v->reverse(0.4f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.8f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.8f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.8f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.8f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					v->turn(-1.f);
				}
				else {
					v->turn(1.f);
				}
			}
		}
	}

}
void Track::pastMajorCurrentMinor(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eTHIRD;
	if (curGear > maxGearAllowed) {
		v->reverse(0.4f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(0.7f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					v->turn(-1.f);
				}
				else {
					v->turn(1.f);
				}
			}
		}
	}
}
void Track::pastMinorCurrentExit(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eFIFTH;
	if (curGear > maxGearAllowed) {
		v->reverse(0.f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
		}
		else if (std::abs(angleToTurn) < 30.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.6f);
			}
			else {
				v->turn(0.6f);
			}
		}
		else if (std::abs(angleToTurn) < 45.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-0.8f);
			}
			else {
				v->turn(0.8f);
			}

		}
		else if (std::abs(angleToTurn) <= 90.f) {
			v->forwards(1.f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				//turn left
				v->turn(-1.f);
			}
			else {
				v->turn(1.f);
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					v->turn(-1.f);
				}
				else {
					v->turn(1.f);
				}
			}
		}
	}
}

// Return value of negative means left turn, postive means right turn
float Track::getAngleToTurnBy(TrackDrivingPoint* currentTarget, Vehicle* v) {
	float angle = 0.f;

	PxVec3 target = PxVec3(currentTarget->x, currentTarget->y, currentTarget->z);

	PxQuat vehicleQuaternion = v->GetTransform().q;
	PxVec3 vehiclePosition = v->GetPosition();

	PxVec3 vehicleFront = vehicleQuaternion.getBasisVector2();
	PxVec3 vehicleFrontNormal = vehicleFront.getNormalized();

	PxVec3 vecToFollow = target - vehiclePosition;
	PxVec3 vecToFollowNormal = vecToFollow.getNormalized();

	
	angle = acos(vehicleFrontNormal.dot(vecToFollowNormal));
	angle = angle * (180.f / M_PI);

	//This tries to turn left
	PxVec3 vehicleLeft = vehicleQuaternion.getBasisVector0();
	PxVec3 vehicleLeftNormal = vehicleLeft.getNormalized();
	float leftDot = vehicleLeftNormal.dot(vecToFollowNormal);

	if (leftDot > 0) {
		angle = -1 * angle;
	}
	
	
	return angle;
}