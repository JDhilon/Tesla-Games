#include "Track.h"

Track::Track() {}
Track::Track(int trackType) {
	if (this->listOfPoints.empty() == true) {
		this->initializeTrackPoints(trackType);
	}
	
}
Track::~Track() {}
void Track::addPointToList(float x, float y, float z, int action) {
	this->listOfPoints.push_back(std::make_unique<TrackDrivingPoint>(x, y, z, action, 0));
}
void Track::addStartPointToList(float x, float y, float z) {
	this->listOfStartPoints.push_back(std::make_unique<TrackDrivingPoint>(x, y, z, trackDrivingPointActions::START_LINE, 0));
}
void Track::addInteractableStripToList() {
	this->listOfLaneStrips.push_back(std::make_unique<TrackInteractableStrip>());
}

void Track::initializeTrackPoints(int trackType) {
	this->listOfPoints.clear();
	this->listOfLaneStrips.clear();
	this->listOfStartPoints.clear();
	
	if (trackType == trackTypeConstants::HYPERLOOP) {
		this->isStarlink = false;
		selectedTrackType = 0;

		this->addStartPointToList(60, 5, -57);
		this->addStartPointToList(60, 5, -66);
		this->addStartPointToList(60, 5, -75);
		this->addStartPointToList(60, 5, -84);

		this->addStartPointToList(70, 5, -57);
		this->addStartPointToList(70, 5, -66);
		this->addStartPointToList(70, 5, -75);
		this->addStartPointToList(70, 5, -84);

		this->addStartPointToList(80, 5, -57);
		this->addStartPointToList(80, 5, -66);
		this->addStartPointToList(80, 5, -75);
		this->addStartPointToList(80, 5, -84);
		
	
		this->addPointToList(69.10, -2.65, -71.48, trackDrivingPointActions::START);
		this->addPointToList(20.70, -2.48, -70.30, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(-34.95, -1.68, -70.95, trackDrivingPointActions::TURN_IN);
		this->addPointToList(-77.63, -2.60, -36.85, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(-69.18, -2.59, 7.72, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(-53.39, -2.59, 31.98, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(1.72, -2.64, 60.39, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(52.33, -2.60, 64.76, trackDrivingPointActions::TURN_EXIT);
		this->addPointToList(78.33, -2.60, 60.76, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(115.87, -2.68, 41.60, trackDrivingPointActions::TURN_IN);
		this->addPointToList(140.58, -2.54, 13.50, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(159.05, -2.68, -22.62, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(130.66, -2.68, -58.69, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(100.00, -2.66, -68.70, trackDrivingPointActions::TURN_EXIT);
    
		//InteractZonePoints
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();

		TrackInteractableStrip& z0 = *this->listOfLaneStrips.at(0);
		z0.addLanePoint(-4.65, -1, -52.59, trackInteractableObjects::TESLA_PICKUP, 0);
		z0.addLanePoint(-4.76, -1.2, -59.96, trackInteractableObjects::AMMO_PICKUP, 0);
		z0.addLanePoint(-4.87, -1.4, -67.33, trackInteractableObjects::TESLA_PICKUP, 0);
		z0.addLanePoint(-4.98, -1.6, -74.7, trackInteractableObjects::AMMO_PICKUP, 0);
		z0.addLanePoint(-5.09, -1.8, -82.07, trackInteractableObjects::TESLA_PICKUP, 0);
		z0.addLanePoint(-5.20, -2, -89.44, trackInteractableObjects::AMMO_PICKUP, 0);

		TrackInteractableStrip& z1 = *this->listOfLaneStrips.at(1);
		//these work
		z1.addLanePoint(-61.8, -2.57, -29.74, trackInteractableObjects::OIL, 3);
		z1.addLanePoint(-69.43, -2.578, -30.524, trackInteractableObjects::EMPTY, 0);
		z1.addLanePoint(-77.07, -2.586, -31.308, trackInteractableObjects::OIL, 3);
		z1.addLanePoint(-84.702, -2.594, -32.092, trackInteractableObjects::OIL, 3);
		z1.addLanePoint(-92.336, -2.602, -32.876, trackInteractableObjects::EMPTY, 0);
		z1.addLanePoint(-99.97, -2.61, -33.66, trackInteractableObjects::OIL, 3);

		TrackInteractableStrip& z2 = *this->listOfLaneStrips.at(2);
		z2.addLanePoint(-26.77, -2.51, 26.78, trackInteractableObjects::TESLA_PICKUP, 1);
		z2.addLanePoint(-29.76, -2.555, 36.17, trackInteractableObjects::AMMO_PICKUP, 0);
		z2.addLanePoint(-32.745, -2.60, 45.56, trackInteractableObjects::TESLA_PICKUP, 1);
		z2.addLanePoint(-35.733, -2.645, 54.96, trackInteractableObjects::AMMO_PICKUP, 0);
		z2.addLanePoint(-38.72, -2.69, 64.35, trackInteractableObjects::TESLA_PICKUP, 1);

		TrackInteractableStrip& z3 = *this->listOfLaneStrips.at(3);
		z3.addLanePoint(31.58, -2.52, 32.87, trackInteractableObjects::EMPTY, 0);
		z3.addLanePoint(32.04, -2.52, 38.85, trackInteractableObjects::CALTROPS, 1);
		z3.addLanePoint(32.81, -2.56, 44.47, trackInteractableObjects::CALTROPS, 1);
		z3.addLanePoint(33.36, -2.59, 50.19, trackInteractableObjects::CALTROPS, 1);
		z3.addLanePoint(34.19, -2.64, 56.29, trackInteractableObjects::CALTROPS, 1);
		z3.addLanePoint(35.12, -2.68, 62.29, trackInteractableObjects::EMPTY, 0);

		TrackInteractableStrip& z4 = *this->listOfLaneStrips.at(4);
		z4.addLanePoint(105.36, -2.45, 16.45, trackInteractableObjects::SMOKE, 2);
		z4.addLanePoint(107.64, -2.516, 33.87, trackInteractableObjects::EMPTY, 0);
		z4.addLanePoint(109.92, -2.582, 40.59, trackInteractableObjects::SMOKE, 2);
		z4.addLanePoint(112.21, -2.648, 47.57, trackInteractableObjects::EMPTY, 0);
		z4.addLanePoint(114.49, -2.714, 56.15, trackInteractableObjects::SMOKE, 2);
		z4.addLanePoint(116.77, -2.78, 54.26, trackInteractableObjects::SMOKE, 2);

		TrackInteractableStrip& z5 = *this->listOfLaneStrips.at(5);
		z5.addLanePoint(132.83, -2.37, -17.07, trackInteractableObjects::CALTROPS, 4);
		z5.addLanePoint(138.33, -2.37, -17.07, trackInteractableObjects::OIL, 4);
		z5.addLanePoint(143.83, -2.37, -17.07, trackInteractableObjects::EMPTY, 0);
		z5.addLanePoint(149.83, -2.37, -17.07, trackInteractableObjects::CALTROPS, 4);
		z5.addLanePoint(155.83, -2.37, -17.07, trackInteractableObjects::OIL, 4);
		z5.addLanePoint(161.83, -2.37, -17.07, trackInteractableObjects::CALTROPS, 4);

	}
	else if (trackType == trackTypeConstants::STARLINK) {
		this->isStarlink = true;
		selectedTrackType = 1;
		this->addStartPointToList(51, 5, -59);
		this->addStartPointToList(51, 5, -66);
		this->addStartPointToList(51, 5, -73);
		this->addStartPointToList(51, 5, -80);

		this->addStartPointToList(61, 5, -59);
		this->addStartPointToList(61, 5, -66);
		this->addStartPointToList(61, 5, -73);
		this->addStartPointToList(61, 5, -80);

		this->addStartPointToList(71, 5, -59);
		this->addStartPointToList(71, 5, -66);
		this->addStartPointToList(71, 5, -73);
		this->addStartPointToList(71, 5, -80);
		
	
		this->addPointToList(95.98, -1.99, -69.30, trackDrivingPointActions::START);
		this->addPointToList(65.58, -1.85, -72.65, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(20.02, -1.69, -76.91, trackDrivingPointActions::TURN_IN);
		this->addPointToList(-48.67, -1.42, -94.54, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(-100.40, -0.95, -143.83, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(-129.06, -0.21, -199.76, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(-120.09, -0.20, -242.94, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(-78.96, 0.44, -282.85, trackDrivingPointActions::TURN_EXIT);
		
		this->addPointToList(85.63, -0.71, -352.00, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(248.30, 0.48, -398.24, trackDrivingPointActions::TURN_IN);
		this->addPointToList(342.84, 0.80, -392.89, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(382.58, 0.48, -369.30, trackDrivingPointActions::TURN_EXIT);
		
		this->addPointToList(391.03, 0.20, -312.03, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(388.08, 0.20, -279.09, trackDrivingPointActions::TURN_IN);
		this->addPointToList(386.78, 0.26, -241.28, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(378.49, 0.24, -246.27, trackDrivingPointActions::TURN_EXIT);

		this->addPointToList(325.29, 0.49, -178.83, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(288.82, 0.64, -143.40, trackDrivingPointActions::TURN_IN);
		this->addPointToList(268.15, -0.68, -94.31, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(288.34, -2.60, -44.34, trackDrivingPointActions::TURN_EXIT);

		this->addPointToList(303.29, -0.12, -22.34, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(329.69, 3.87, 1.55, trackDrivingPointActions::TURN_IN);
		this->addPointToList(360.60, 6.92, 48.36, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(324.48, 0.91, 131.67, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(235.04, -0.81, 158.35, trackDrivingPointActions::APEX_MINOR);
		this->addPointToList(187.04, -0.94, 130.97, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(171.73, -1.01, 85.73, trackDrivingPointActions::TURN_EXIT);

		this->addPointToList(175.50, -1.05, 43.83, trackDrivingPointActions::SLOW_DOWN);
		this->addPointToList(189.69, -1.60, 1.65, trackDrivingPointActions::TURN_IN);
		this->addPointToList(163.57, -2.39, -58.84, trackDrivingPointActions::APEX_MAJOR);
		this->addPointToList(138.60, -2.22, -72.44, trackDrivingPointActions::TURN_EXIT);


		//InteractZonePoints
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		this->addInteractableStripToList();
		

		TrackInteractableStrip& z0 = *this->listOfLaneStrips.at(0);
		z0.addLanePoint(8, -1.65, -90.6, trackInteractableObjects::AMMO_PICKUP, 0);
		z0.addLanePoint(8, -1.65, -84.6, trackInteractableObjects::TESLA_PICKUP, 0);
		z0.addLanePoint(8, -1.65, -78.6, trackInteractableObjects::AMMO_PICKUP, 0);
		z0.addLanePoint(8, -1.65, -72.6, trackInteractableObjects::TESLA_PICKUP, 0);
		z0.addLanePoint(8, -1.65, -66.6, trackInteractableObjects::AMMO_PICKUP, 0);

		TrackInteractableStrip& z1 = *this->listOfLaneStrips.at(1);
		z1.addLanePoint(-69.5, -1.15, -137, trackInteractableObjects::TESLA_PICKUP, 0);
		z1.addLanePoint(-74.5, -1.15, -133, trackInteractableObjects::AMMO_PICKUP, 0);
		z1.addLanePoint(-79.5, -1.15, -129, trackInteractableObjects::TESLA_PICKUP, 0);
		z1.addLanePoint(-84.5, -1.15, -125, trackInteractableObjects::AMMO_PICKUP, 0);
		z1.addLanePoint(-89.5, -1.15, -121, trackInteractableObjects::TESLA_PICKUP, 0);

		TrackInteractableStrip& z2 = *this->listOfLaneStrips.at(2);
		z2.addLanePoint(-116, 0.06, -224, trackInteractableObjects::SMOKE, 1);
		z2.addLanePoint(-121, 0.13, -226, trackInteractableObjects::SMOKE, 1);
		z2.addLanePoint(-126, 0.20, -228, trackInteractableObjects::EMPTY, 0);
		z2.addLanePoint(-131, 0.27, -230, trackInteractableObjects::SMOKE, 1);
		z2.addLanePoint(-136, 0.34, -232, trackInteractableObjects::SMOKE, 1);

		TrackInteractableStrip& z3 = *this->listOfLaneStrips.at(3);
		z3.addLanePoint(20, -0.46, -307, trackInteractableObjects::OIL, 2);
		z3.addLanePoint(17, -0.35, -313, trackInteractableObjects::EMPTY, 0);
		z3.addLanePoint(13, -0.24, -319, trackInteractableObjects::OIL, 2);
		z3.addLanePoint(10, -0.16, -325, trackInteractableObjects::CALTROPS, 2);
		z3.addLanePoint(7, -0.07, -331, trackInteractableObjects::OIL, 2);

		TrackInteractableStrip& z4 = *this->listOfLaneStrips.at(4);
		z4.addLanePoint(219, 0.42, -406, trackInteractableObjects::CALTROPS, 1);
		z4.addLanePoint(221, 0.32, -400, trackInteractableObjects::CALTROPS, 1);
		z4.addLanePoint(222, 0.26, -394, trackInteractableObjects::CALTROPS, 1);
		z4.addLanePoint(223, 0.16, -388, trackInteractableObjects::EMPTY, 0);
		z4.addLanePoint(224, 0.11, -382, trackInteractableObjects::CALTROPS, 1);

		TrackInteractableStrip& z5 = *this->listOfLaneStrips.at(5);
		z5.addLanePoint(381, 0.19, -316, trackInteractableObjects::TESLA_PICKUP, 0);
		z5.addLanePoint(387, 0.21, -316, trackInteractableObjects::AMMO_PICKUP, 0);
		z5.addLanePoint(393, 0.23, -316, trackInteractableObjects::TESLA_PICKUP, 0);
		z5.addLanePoint(399, 0.25, -316, trackInteractableObjects::AMMO_PICKUP, 0);
		z5.addLanePoint(405, 0.27, -316, trackInteractableObjects::TESLA_PICKUP, 0);

		TrackInteractableStrip& z6 = *this->listOfLaneStrips.at(6);
		z6.addLanePoint(317, 0.47, -182, trackInteractableObjects::SMOKE, 2);
		z6.addLanePoint(322, 0.49, -177, trackInteractableObjects::OIL, 2);
		z6.addLanePoint(327, 0.51, -172, trackInteractableObjects::SMOKE, 2);
		z6.addLanePoint(332, 0.52, -167, trackInteractableObjects::OIL, 2);
		z6.addLanePoint(337, 0.53, -162, trackInteractableObjects::SMOKE, 2);

		TrackInteractableStrip& z7 = *this->listOfLaneStrips.at(7);
		z7.addLanePoint(270, -3.72, -57, trackInteractableObjects::SMOKE, 2);
		z7.addLanePoint(275, -3.41, -60, trackInteractableObjects::OIL, 2);
		z7.addLanePoint(280, -3.11, -63, trackInteractableObjects::SMOKE, 2);
		z7.addLanePoint(285, -2.81, -66, trackInteractableObjects::OIL, 2);
		z7.addLanePoint(290, -2.52, -69, trackInteractableObjects::EMPTY, 0);

		TrackInteractableStrip& z8 = *this->listOfLaneStrips.at(8);
		z8.addLanePoint(190, -1.31, 19.21, trackInteractableObjects::OIL, 2);
		z8.addLanePoint(184, -1.34, 18.32, trackInteractableObjects::SMOKE, 2);
		z8.addLanePoint(178, -1.36, 17.36, trackInteractableObjects::CALTROPS, 2);
		z8.addLanePoint(172, -1.39, 16.40, trackInteractableObjects::OIL, 2);
		z8.addLanePoint(166, -1.42, 15.51, trackInteractableObjects::SMOKE, 2);

	}
}

//To use if you get stuck
void Track::performStuckCorrectionMove(Vehicle* v) {
	TrackDrivingPoint* currentTarget = &v->curTarget;
	float angleToTurn = getAngleToTurnBy(currentTarget, v);

	if (angleToTurn < 0) {
		v->forwards(0.f);
		v->turn(0.4f); //going in reverse
		v->reverse(0.9f);
	}
	else {
		v->forwards(0.f);
		v->turn(-0.4f);
		v->reverse(0.9f);
	}
	
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
		this->pastTurnExitCurrentSlowDown(curGear, angleToTurn, v);
	}
	else if (pastAction == trackDrivingPointActions::TURN_EXIT && currentAction == trackDrivingPointActions::START) {
		this->pastTurnExitCurrentStart(curGear, angleToTurn, v);
	}

	//******************************************************************************************************************
	//**************************************** TURNING STUFF ***********************************************************
	//******************************************************************************************************************
	else if ( (pastAction == trackDrivingPointActions::SLOW_DOWN || pastAction == trackDrivingPointActions::TURN_EXIT) 
				&& currentAction == trackDrivingPointActions::TURN_IN) {
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
			v->forwards(0.8f);
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
			v->forwards(0.7f);
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
			v->forwards(0.6f);
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
					v->turn(-0.9f);
				}
				else {
					v->turn(0.9f);
				}
			}
		}
		else {
			float sideways = std::abs(v->gVehicle4W->computeSidewaysSpeed());
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());

			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
}
void Track::pastTurnExitCurrentSlowDown(PxU32 curGear, float angleToTurn, Vehicle* v) {
	if (std::abs(angleToTurn) < 5.f) {
		v->turn(0.f);
		v->forwards(1.f);
		v->reverse(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.9f);
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
			v->forwards(0.7f);
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
			v->forwards(0.6f);
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
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());

			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}
					
				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
}
void Track::pastTurnExitCurrentStart(PxU32 curGear, float angleToTurn, Vehicle* v) {
	if (std::abs(angleToTurn) < 5.f) {
		v->turn(0.f);
		v->forwards(1.f);
		v->reverse(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(0.9f);
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
			v->forwards(0.8f);
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
			v->forwards(0.7f);
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
			v->forwards(0.6f);
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
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());

			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
}





void Track::pastSlowDownCurrentTurnIn(PxU32 curGear, float angleToTurn, Vehicle* v) {
	if (curGear > PxVehicleGearsData::eFOURTH) {
		if (std::abs(angleToTurn) < 10.f) {
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
			v->reverse(0.3f);
			v->forwards(0.f);
		}
	}
	else if (curGear <= PxVehicleGearsData::eSECOND) {
		if (std::abs(angleToTurn) < 5.f) {
			v->turn(0.f);
			v->forwards(1.f);
			v->reverse(0.f);
		}
		else {
			v->forwards(0.8f);
			v->reverse(0.f);
			if (angleToTurn < 0) {
				v->turn(-0.4f);
			}
			else {
				v->turn(0.4f);
			}
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
			if (std::abs(angleToTurn) > 90.f) {
				v->forwards(0.7f);
			}
			else {
				v->forwards(0.2f);
			}
			
		}
	}
}

void Track::pastTurnInCurrentMajor(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = PxVehicleGearsData::eTHIRD;
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
			v->forwards(0.6f);
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
			v->forwards(0.5f);
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
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
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
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
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
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}
	
}
void Track::pastMinorCurrentMajor(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = this->isStarlink ? PxVehicleGearsData::eFIFTH : PxVehicleGearsData::eFOURTH;
	if (curGear > maxGearAllowed) {
		v->reverse(0.4f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(this->isStarlink ? 1.f: 0.85f);
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
			v->forwards(this->isStarlink ? 0.9f : 0.8f);
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
			v->forwards(this->isStarlink ? 0.85f : 0.8f);
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
			v->forwards(this->isStarlink ? 0.85f : 0.8f);
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
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
				}
			}
		}
	}

}
void Track::pastMajorCurrentMinor(PxU32 curGear, float angleToTurn, Vehicle* v) {
	PxU32 maxGearAllowed = this->isStarlink ? PxVehicleGearsData::eFIFTH : PxVehicleGearsData::eFOURTH;
	if (curGear > maxGearAllowed) {
		v->reverse(0.4f);
		v->forwards(0.f);
	}
	else {
		if (std::abs(angleToTurn) < 15.f) {
			v->forwards(this->isStarlink ? 0.9f : 0.7f);
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
			v->forwards(this->isStarlink ? 0.9f : 0.7f);
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
			v->forwards(this->isStarlink ? 0.85f : 0.7f);
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
			v->forwards(this->isStarlink ? 0.85f : 0.7f);
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
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
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
			float forwards = std::abs(v->gVehicle4W->computeForwardSpeed());
			//For the cases where vehicle is spiining out, cuz why else would you be more than 90 degrees from a point
			if (sideways > 1.4f) {
				v->turn(0.f);
				v->reverse(0.f);
				v->forwards(0.f);
			}
			else {
				v->forwards(1.f);
				if (angleToTurn < 0) {
					if (forwards < 3.f) {
						v->turn(-1.f);
					}
					else {
						v->turn(-0.7f);
					}

				}
				else {
					if (forwards < 3.f) {
						v->turn(1.f);
					}
					else {
						v->turn(0.7f);
					}
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

//adds the correct lap markers to the vector
void Track::initializeLapMarkers(int trackType)
{
	lapMarkers.clear();
	if (trackType == trackTypeConstants::HYPERLOOP) {
		for (int i = 0; i < 5; i++) {
			LapMarker* l = new LapMarker(i);
			lapMarkers.push_back(l);
		}

		lapMarkers[0]->position = PxVec3(52.5f, -1.f, -74.f);	//start/finish line
		lapMarkers[0]->dimensions = PxVec3(1, 5, 23);
		lapMarkers[1]->position = PxVec3(7.f, -1.f, -72.5f);
		lapMarkers[1]->dimensions = PxVec3(1, 5, 23);
		lapMarkers[2]->position = PxVec3(-78.f, -1.f, -2.75f);
		lapMarkers[2]->dimensions = PxVec3(21, 5, 8);
		lapMarkers[3]->position = PxVec3(54.5f, -1.f, 49.f);
		lapMarkers[3]->dimensions = PxVec3(5, 5, 22);
		lapMarkers[4]->position = PxVec3(150.5f, -1.f, -7.5f);
		lapMarkers[4]->dimensions = PxVec3(22, 5, 3);
		

	}
	else if (trackType == trackTypeConstants::STARLINK) {
		for (int i = 0; i < 14; i++) {
			LapMarker* l = new LapMarker(i);
			lapMarkers.push_back(l);
		}

		lapMarkers[0]->position = PxVec3(49.f, -1.f, -72.5f);	//start/finish line
		lapMarkers[0]->dimensions = PxVec3(4, 15, 18);
		lapMarkers[1]->position = PxVec3(-65.f, -1.f, -115.5f);	
		lapMarkers[1]->dimensions = PxVec3(13, 15, 14);
		lapMarkers[2]->position = PxVec3(-111.f, -1.f, -250.f);	
		lapMarkers[2]->dimensions = PxVec3(13, 15, 13);
		lapMarkers[3]->position = PxVec3(186.f, -1.f, -380.5f);	
		lapMarkers[3]->dimensions = PxVec3(8, 15, 17);
		lapMarkers[4]->position = PxVec3(333.f, -1.f, -403.f);	
		lapMarkers[4]->dimensions = PxVec3(7, 15, 17);
		lapMarkers[5]->position = PxVec3(377.25f, -1.f, -367.25f);	
		lapMarkers[5]->dimensions = PxVec3(16, 15, 10);
		lapMarkers[6]->position = PxVec3(389.f, -1.f, -256.f);	
		lapMarkers[6]->dimensions = PxVec3(16, 15, 6);
		lapMarkers[7]->position = PxVec3(285.5f, -1.f, -137.f);	
		lapMarkers[7]->dimensions = PxVec3(13, 15, 13);
		lapMarkers[8]->position = PxVec3(277.f, -1.f, -69.5f);	
		lapMarkers[8]->dimensions = PxVec3(15, 15, 9);
		lapMarkers[9]->position = PxVec3(361.5f, -1.f, 34.f);	
		lapMarkers[9]->dimensions = PxVec3(17, 15, 6);
		lapMarkers[10]->position = PxVec3(329.f, -1.f, 134.5f);	
		lapMarkers[10]->dimensions = PxVec3(12, 15, 13);
		lapMarkers[11]->position = PxVec3(202.f, -1.f, 148.5f);	
		lapMarkers[11]->dimensions = PxVec3(9, 15, 15);
		lapMarkers[12]->position = PxVec3(166.5f, -1.f, 68.5f);	
		lapMarkers[12]->dimensions = PxVec3(17, 15, 5);
		lapMarkers[13]->position = PxVec3(179.f, -1.f, -29.f);	
		lapMarkers[13]->dimensions = PxVec3(16, 15, 5);
	}
}
