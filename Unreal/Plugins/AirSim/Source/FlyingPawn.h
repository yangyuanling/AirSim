#pragma once

#include <memory>
#include "VehiclePawnBase.h"
#include "controllers/DroneCommon.hpp"
#include "FlyingPawn.generated.h"

UCLASS()
class AIRSIM_API AFlyingPawn : public AVehiclePawnBase
{
	GENERATED_BODY()

public: //interface
    typedef msr::airlib::RCData RCData;

	void setRotorSpeed(int rotor_index, float radsPerSec);
    std::string getVehicleName();

    const RCData& getRCData();

public:
    //overrides from VehiclePawnBase
    virtual APIPCamera* getFpvCamera() override;
    virtual void initialize() override;
    virtual void reset() override;

public: //blueprint properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debugging")
		float RotatorFactor = 1.0f;

	//HIL settings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HIL")
		FString VehicleName = "Pixhawk";

private: //methods
	void setupComponentReferences();
	void setStencilIDs();
    void setupInputBindings();

    void inputEventThrottle(float val);
    void inputEventYaw(float val);
    void inputEventPitch(float val);
    void inputEventRoll(float val);
    void inputEventArmDisArm();

private: //variables
		 //Unreal components
	static constexpr size_t rotor_count = 4;
	UPROPERTY() APIPCamera* fpv_camera_;
	UPROPERTY() URotatingMovementComponent* rotating_movements_[rotor_count];

    RCData rc_data;
};
