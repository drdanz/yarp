/*
 * Copyright (C) 2012 Robotics Brain and Cognitive Sciences Department, Istituto Italiano di Tecnologia
 * Authors: Lorenzo Natale
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_DEV_IMPLEMENTCONTROLBOARDINTERFACES_H
#define YARP_DEV_IMPLEMENTCONTROLBOARDINTERFACES_H

#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/api.h>

namespace yarp{
    namespace dev {
        template <class DERIVED, class IMPLEMENT> class ImplementPositionControl;
        template <class DERIVED, class IMPLEMENT> class ImplementVelocityControl;
        template <class DERIVED, class IMPLEMENT> class ImplementEncoders;
        template <class DERIVED, class IMPLEMENT> class ImplementAmplifierControl;
        template <class DERIVED, class IMPLEMENT> class ImplementControlCalibration;
        template <class DERIVED, class IMPLEMENT> class ImplementControlLimits;
        template <class DERIVED, class IMPLEMENT> class ImplementControlCalibration2;
        class StubImplPositionControlRaw;
        class StubImplEncodersRaw;
    }
}


/**
 * Default implementation of the IPositionControl interface. This template class can
 * be used to easily provide an implementation of IPositionControl. It takes two
 * arguments, the class it is derived from and the class it is implementing, typically
 * IPositionControl (which should probably be removed from the template arguments).
 * "<IMPLEMENT>" makes only explicit that the class is implementing IPositionControl and
 * appears in the inheritance list of the derived class.
 *
 * Important: these templates are here for backward compatibility, newer implementations
 * are done with normal classes. If you need to implement something similar have a look
 * at implementations of other interfaes (e.g ITorqueControl).
 */
template <class DERIVED, class IMPLEMENT>
class yarp::dev::ImplementPositionControl : public IMPLEMENT
{
protected:
    IPositionControlRaw *iPosition;
    void *helper;
    double *temp;
    /**
     * Initialize the internal data and alloc memory.
     * @param size is the number of controlled axes the driver deals with.
     * @param amap is a lookup table mapping axes onto physical drivers.
     * @param enc is an array containing the encoder to angles conversion factors.
     * @param zos is an array containing the zeros of the encoders.
     *  respect to the control/output values of the driver.
     * @return true if initialized succeeded, false if it wasn't executed, or assert.
     */
    bool initialize (int size, const int *amap, const double *enc, const double *zos);

    /**
     * Clean up internal data and memory.
     * @return true if uninitialization is executed, false otherwise.
     */
    bool uninitialize ();

public:
    /**
     * Constructor.
     * @param y is the pointer to the class instance inheriting from this
     *  implementation.
     */
    ImplementPositionControl(DERIVED *y);

    /**
     * Destructor. Perform uninitialize if needed.
     */
    virtual ~ImplementPositionControl();


    /**
     * Get the number of controlled axes. This command asks the number of controlled
     * axes for the current physical interface.
     * @return the number of controlled axes.
     */
    virtual bool getAxes(int *axis) YARP_OVERRIDE;

    virtual bool positionMove(int j, double ref) YARP_OVERRIDE;
    virtual bool positionMove(const double *refs) YARP_OVERRIDE;
    virtual bool relativeMove(int j, double delta) YARP_OVERRIDE;
    virtual bool relativeMove(const double *deltas) YARP_OVERRIDE;
    virtual bool checkMotionDone(bool *flag) YARP_OVERRIDE;
    virtual bool checkMotionDone(int j, bool *flag) YARP_OVERRIDE;
    virtual bool setRefSpeed(int j, double sp) YARP_OVERRIDE;
    virtual bool setRefSpeeds(const double *spds) YARP_OVERRIDE;
    virtual bool setRefAcceleration(int j, double acc) YARP_OVERRIDE;
    virtual bool setRefAccelerations(const double *accs) YARP_OVERRIDE;
    virtual bool getRefSpeed(int j, double *ref) YARP_OVERRIDE;
    virtual bool getRefSpeeds(double *spds) YARP_OVERRIDE;
    virtual bool getRefAcceleration(int j, double *acc) YARP_OVERRIDE;
    virtual bool getRefAccelerations(double *accs) YARP_OVERRIDE;
    virtual bool stop(int j) YARP_OVERRIDE;
    virtual bool stop() YARP_OVERRIDE;
};

/**
 * Default implementation of the IVelocityControl interface. This template class can
 * be used to easily provide an implementation of IVelocityControl. It takes two
 * arguments, the class it is derived from and the class it is implementing, typically
 * IVelocityControl (which should probably be removed from the template arguments).
 * "<IMPLEMENT>" makes only explicit that the class is implementing IVelocityControl and
 * appears in the inheritance list of the derived class.
 */
template <class DERIVED, class IMPLEMENT>
class yarp::dev::ImplementVelocityControl : public IMPLEMENT
{
protected:
    IVelocityControlRaw *iVelocity;
    void *helper;
    double *temp;

    /**
     * Initialize the internal data and alloc memory.
     * @param size is the number of controlled axes the driver deals with.
     * @param amap is a lookup table mapping axes onto physical drivers.
     * @param enc is an array containing the encoder to angles conversion factors.
     * @param zos is an array containing the zeros of the encoders.
     * @return true if initialized succeeded, false if it wasn't executed, or assert.
     */
    bool initialize (int size, const int *amap, const double *enc, const double *zos);

    /**
     * Clean up internal data and memory.
     * @return true if uninitialization is executed, false otherwise.
     */
    bool uninitialize ();

public:
    /**
     * Constructor.
     * @param y is the pointer to the class instance inheriting from this
     *  implementation.
     */
    ImplementVelocityControl(DERIVED *y);

    /**
     * Destructor. Perform uninitialize if needed.
     */
    virtual ~ImplementVelocityControl();

    virtual bool getAxes(int *axes) YARP_OVERRIDE;

    virtual bool velocityMove(int j, double v) YARP_OVERRIDE;
    virtual bool velocityMove(const double *v) YARP_OVERRIDE;
    virtual bool setRefAcceleration(int j, double acc) YARP_OVERRIDE;
    virtual bool setRefAccelerations(const double *accs) YARP_OVERRIDE;
    virtual bool getRefAcceleration(int j, double *acc) YARP_OVERRIDE;
    virtual bool getRefAccelerations(double *accs) YARP_OVERRIDE;
    virtual bool stop(int j) YARP_OVERRIDE;
    virtual bool stop() YARP_OVERRIDE;
};

template <class DERIVED, class IMPLEMENT>
class yarp::dev::ImplementEncoders : public IMPLEMENT
{
protected:
    IEncodersRaw *iEncoders;
    void *helper;
    double *temp;

    /**
     * Initialize the internal data and alloc memory.
     * @param size is the number of controlled axes the driver deals with.
     * @param amap is a lookup table mapping axes onto physical drivers.
     * @param enc is an array containing the encoder to angles conversion factors.
     * @param zos is an array containing the zeros of the encoders.
     * @return true if initialized succeeded, false if it wasn't executed, or assert.
     */
    bool initialize (int size, const int *amap, const double *enc, const double *zos);

    /**
     * Clean up internal data and memory.
     * @return true if uninitialization is executed, false otherwise.
     */
    bool uninitialize ();

public:
    /* Constructor.
     * @param y is the pointer to the class instance inheriting from this
     *  implementation.
     */
    ImplementEncoders(DERIVED *y);

    /**
     * Destructor. Perform uninitialize if needed.
     */
    virtual ~ImplementEncoders();


    /**
     * Get the number of controlled axes. This command asks the number of controlled
     * axes for the current physical interface.
     * @return the number of controlled axes.
     */
    virtual bool getAxes(int *ax) YARP_OVERRIDE;

    /**
     * Reset encoder, single joint. Set the encoder value to zero
     * @param j encoder number
     * @return true/false
     */
    virtual bool resetEncoder(int j) YARP_OVERRIDE;

    /**
     * Reset encoders. Set the encoders value to zero
     * @return true/false
     */
    virtual bool resetEncoders() YARP_OVERRIDE;

    /**
     * Set the value of the encoder for a given joint.
     * @param j encoder number
     * @param val new value
     * @return true/false
     */
    virtual bool setEncoder(int j, double val) YARP_OVERRIDE;

    /**
     * Set the value of all encoders.
     * @param vals pointer to the new values
     * @return true/false
     */
    virtual bool setEncoders(const double *vals) YARP_OVERRIDE;

    /**
     * Read the value of an encoder.
     * @param j encoder number
     * @param v pointer to storage for the return value
     * @return true/false, upon success/failure (you knew it, uh?)
     */
    virtual bool getEncoder(int j, double *v) YARP_OVERRIDE;

    /**
     * Read the position of all axes.
     * @param encs pointer to the array that will contain the output
     * @return true/false on success/failure
     */
    virtual bool getEncoders(double *encs) YARP_OVERRIDE;

    /**
     * Read the instantaneous speed of an axis.
     * @param j axis number
     * @param spds pointer to storage for the output
     * @return true if successful, false ... otherwise.
     */
    virtual bool getEncoderSpeed(int j, double *spds) YARP_OVERRIDE;

    /**
     * Read the instantaneous speed of all axes.
     * @param spds pointer to storage for the output values
     * @return guess what? (true/false on success or failure).
     */
    virtual bool getEncoderSpeeds(double *spds) YARP_OVERRIDE;

    /**
     * Read the instantaneous acceleration of an axis.
     * @param j axis number
     * @param spds pointer to the array that will contain the output
     */
    virtual bool getEncoderAcceleration(int j, double *spds) YARP_OVERRIDE;

    /**
     * Read the instantaneous acceleration of all axes.
     * @param accs pointer to the array that will contain the output
     * @return true if all goes well, false if anything bad happens.
     */
    virtual bool getEncoderAccelerations(double *accs) YARP_OVERRIDE;
};

template <class DERIVED, class IMPLEMENT>
class yarp::dev::ImplementControlCalibration: public IMPLEMENT
{
protected:
    IControlCalibrationRaw *iCalibrate;
    void *helper;
    double *temp;

    /**
     * Initialize the internal data and alloc memory.
     * @param size is the number of controlled axes the driver deals with.
     * @param amap is a lookup table mapping axes onto physical drivers.
     * @param enc is an array containing the encoder to angles conversion factors.
     * @param zos is an array containing the zeros of the encoders.
     * @return true if initialized succeeded, false if it wasn't executed, or assert.
     */
    bool initialize (int size, const int *amap, const double *enc, const double *zos);

    /**
     * Clean up internal data and memory.
     * @return true if uninitialization is executed, false otherwise.
     */
    bool uninitialize ();

public:
    /* Constructor.
     * @param y is the pointer to the class instance inheriting from this
     *  implementation.
     */
    ImplementControlCalibration(DERIVED *y);

    /**
     * Destructor. Perform uninitialize if needed.
     */
    virtual ~ImplementControlCalibration();

    virtual bool calibrate(int j, double p) YARP_OVERRIDE;

    virtual bool done(int j) YARP_OVERRIDE;
};

template <class DERIVED, class IMPLEMENT>
class yarp::dev::ImplementControlLimits: public IMPLEMENT
{
protected:
    IControlLimitsRaw *iLimits;
    void *helper;
    double *temp;

    /**
     * Initialize the internal data and alloc memory.
     * @param size is the number of controlled axes the driver deals with.
     * @param amap is a lookup table mapping axes onto physical drivers.
     * @param enc is an array containing the encoder to angles conversion factors.
     * @param zos is an array containing the zeros of the encoders.
     * @return true if initialized succeeded, false if it wasn't executed, or assert.
     */
    bool initialize (int size, const int *amap, const double *enc, const double *zos);

    /**
     * Clean up internal data and memory.
     * @return true if uninitialization is executed, false otherwise.
     */
    bool uninitialize ();

public:
    /* Constructor.
     * @param y is the pointer to the class instance inheriting from this
     *  implementation.
     */
    ImplementControlLimits(DERIVED *y);

    /**
     * Destructor. Perform uninitialize if needed.
     */
    virtual ~ImplementControlLimits();

    /* Set the software limits for a particular axis, the behavior of the
     * control card when these limits are exceeded, depends on the implementation.
     * @param axis joint number
     * @param min the value of the lower limit
     * @param max the value of the upper limit
     * @return true or false on success or failure
     */
    virtual bool setLimits(int axis, double min, double max) YARP_OVERRIDE;

    /* Get the software limits for a particular axis.
     * @param axis joint number
     * @param pointer to store the value of the lower limit
     * @param pointer to store the value of the upper limit
     * @return true if everything goes fine, false if something bad happens (yes, sometimes life is tough)
     */
    virtual bool getLimits(int axis, double *min, double *max) YARP_OVERRIDE;
};


template <class DERIVED, class IMPLEMENT>
class yarp::dev::ImplementAmplifierControl: public IMPLEMENT
{
protected:
    IAmplifierControlRaw *iAmplifier;
    void *helper;
    double *dTemp;
    int *iTemp;

    /**
     * Initialize the internal data and alloc memory.
     * @param size is the number of controlled axes the driver deals with.
     * @param amap is a lookup table mapping axes onto physical drivers.
     * @param enc is an array containing the encoder to angles conversion factors.
     * @param zos is an array containing the zeros of the encoders.
     * @return true if initialized succeeded, false if it wasn't executed, or assert.
     */
    bool initialize (int size, const int *amap, const double *enc, const double *zos, const double *ampereFactor=NULL, const double *voltFactor=NULL);

    /**
     * Clean up internal data and memory.
     * @return true if uninitialization is executed, false otherwise.
     */
    bool uninitialize ();

public:
    /* Constructor.
     * @param y is the pointer to the class instance inheriting from this
     *  implementation.
     */
    ImplementAmplifierControl(DERIVED *y);

    /**
     * Destructor. Perform uninitialize if needed.
     */
    virtual ~ImplementAmplifierControl();

    /** Enable the amplifier on a specific joint. Be careful, check that the output
     * of the controller is appropriate (usually zero), to avoid
     * generating abrupt movements.
     * @return true/false on success/failure
     */
    virtual bool enableAmp(int j) YARP_OVERRIDE;

    /** Disable the amplifier on a specific joint. All computations within the board
     * will be carried out normally, but the output will be disabled.
     * @return true/false on success/failure
     */
    virtual bool disableAmp(int j) YARP_OVERRIDE;

    /* Get the status of the amplifiers, coded in a 32 bits integer for
     * each amplifier (at the moment contains only the fault, it will be
     * expanded in the future).
     * @param st pointer to storage
     * @return true in good luck, false otherwise.
     */
    virtual bool getAmpStatus(int *st) YARP_OVERRIDE;

    virtual bool getAmpStatus(int j, int *st) YARP_OVERRIDE;

    /* Read the electric current going to all motors.
     * @param vals pointer to storage for the output values
     * @return hopefully true, false in bad luck.
     */
    virtual bool getCurrents(double *vals) YARP_OVERRIDE;

    /* Read the electric current going to a given motor.
     * @param j motor number
     * @param val pointer to storage for the output value
     * @return probably true, might return false in bad times
     */
    virtual bool getCurrent(int j, double *val) YARP_OVERRIDE;

    /* Set the maximum electric current going to a given motor. The behavior
     * of the board/amplifier when this limit is reached depends on the
     * implementation.
     * @param j motor number
     * @param v the new value
     * @return probably true, might return false in bad times
     */
    virtual bool setMaxCurrent(int j, double v) YARP_OVERRIDE;

    /**
    * Returns the maximum electric current allowed for a given motor. The behavior
    * of the board/amplifier when this limit is reached depends on the
    * implementation.
    * @param j motor number
    * @param v the return value
    * @return probably true, might return false in bad times
    */
    virtual bool getMaxCurrent(int j, double *v) YARP_OVERRIDE;

    /* Get the the nominal current which can be kept for an indefinite amount of time
     * without harming the motor. This value is specific for each motor and it is typically
     * found in its datasheet. The units are Ampere.
     * This value and the peak current may be used by the firmware to configure
     * an I2T filter.
     * @param j joint number
     * @param val storage for return value. [Ampere]
     * @return true/false success failure.
     */
    virtual bool getNominalCurrent(int m, double *val) YARP_OVERRIDE;

    /* Get the the peak current which causes damage to the motor if maintained
     * for a long amount of time.
     * The value is often found in the motor datasheet, units are Ampere.
     * This value and the nominal current may be used by the firmware to configure
     * an I2T filter.
     * @param j joint number
     * @param val storage for return value. [Ampere]
     * @return true/false success failure.
     */
    virtual bool getPeakCurrent(int m, double *val) YARP_OVERRIDE;

    /* Set the the peak current. This value  which causes damage to the motor if maintained
     * for a long amount of time.
     * The value is often found in the motor datasheet, units are Ampere.
     * This value and the nominal current may be used by the firmware to configure
     * an I2T filter.
     * @param j joint number
     * @param val storage for return value. [Ampere]
     * @return true/false success failure.
     */
    virtual bool setPeakCurrent(int m, const double val) YARP_OVERRIDE;

    /* Get the the current PWM value used to control the motor.
     * The units are firmware dependent, either machine units or percentage.
     * @param j joint number
     * @param val filled with PWM value.
     * @return true/false success failure.
     */
    virtual bool getPWM(int j, double* val) YARP_OVERRIDE;

    /* Get the PWM limit fot the given motor.
     * The units are firmware dependent, either machine units or percentage.
     * @param j joint number
     * @param val filled with PWM limit value.
     * @return true/false success failure.
     */
    virtual bool getPWMLimit(int j, double* val) YARP_OVERRIDE;

    /* Set the PWM limit fot the given motor.
     * The units are firmware dependent, either machine units or percentage.
     * @param j joint number
     * @param val new value for the PWM limit.
     * @return true/false success failure.
     */
    virtual bool setPWMLimit(int j, const double val) YARP_OVERRIDE;

    /* Get the power source voltage for the given motor in Volt.
     * @param j joint number
     * @param val filled with return value.
     * @return true/false success failure.
     */
    virtual bool getPowerSupplyVoltage(int j, double* val) YARP_OVERRIDE;
};

template <class DERIVED, class IMPLEMENT>
class yarp::dev::ImplementControlCalibration2: public IMPLEMENT
{
protected:
    IControlCalibration2Raw *iCalibrate;
    void *helper;
    double *temp;

    /**
     * Initialize the internal data and alloc memory.
     * @param size is the number of controlled axes the driver deals with.
     * @param amap is a lookup table mapping axes onto physical drivers.
     * @param enc is an array containing the encoder to angles conversion factors.
     * @param zos is an array containing the zeros of the encoders.
     * @return true if initialized succeeded, false if it wasn't executed, or assert.
     */
    bool initialize (int size, const int *amap, const double *enc, const double *zos);

    /**
     * Clean up internal data and memory.
     * @return true if uninitialization is executed, false otherwise.
     */
    bool uninitialize ();

public:
    /* Constructor.
     * @param y is the pointer to the class instance inheriting from this
     *  implementation.
     */
    ImplementControlCalibration2(DERIVED *y);

    /**
     * Destructor. Perform uninitialize if needed.
     */
    virtual ~ImplementControlCalibration2();

    virtual bool calibrate2(int axis, unsigned int type, double p1, double p2, double p3) YARP_OVERRIDE;

    virtual bool setCalibrationParameters(int axis, const CalibrationParameters& params) YARP_OVERRIDE;

    virtual bool done(int j) YARP_OVERRIDE;
};

/**
 * Stub implementation of IPositionControlRaw interface.
 * Inherit from this class if you want a stub implementation
 * of methods in IPositionControlRaw. This class allows to
 * gradually implement an interface; you just have to implement
 * functions that are useful for the underlying device.
 * Another way to see this class is as a means to convert
 * compile time errors in runtime errors.
 *
 * If you use this class please be aware that the device
 * you are wrapping might not function properly because you
 * missed to implement useful functionalities.
 *
 */
class YARP_dev_API yarp::dev::StubImplPositionControlRaw: public IPositionControlRaw
{
private:
    /**
     * Helper for printing error message, see below.
     * Implemented in ControlBoardInterfacesImpl.cpp.
     */
    bool NOT_YET_IMPLEMENTED(const char *func=0);

public:
    virtual ~StubImplPositionControlRaw(){}

    virtual bool getAxes(int *ax) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getAxes");}

    virtual bool positionMoveRaw(int j, double ref) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("positionMoveRaw");}

    virtual bool positionMoveRaw(const double *refs) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("positionMoveRaw");}

    virtual bool relativeMoveRaw(int j, double delta) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("relativeMoveRaw");}

    virtual bool relativeMoveRaw(const double *deltas) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("relativeMoveRaw");}

    virtual bool checkMotionDoneRaw(int j, bool *flag) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("checkMotionDoneRaw");}

    virtual bool checkMotionDoneRaw(bool *flag) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("checkMotionDoneRaw");}

    virtual bool setRefSpeedRaw(int j, double sp) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("setRefSpeedRaw");}

    virtual bool setRefSpeedsRaw(const double *spds) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("setRefSpeedsRaw");}

    virtual bool setRefAccelerationRaw(int j, double acc) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("setRefAccelerationRaw");}

    virtual bool setRefAccelerationsRaw(const double *accs) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("setRefAccelerationsRaw");}

    virtual bool getRefSpeedRaw(int j, double *ref) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getRefSpeedRaw");}

    virtual bool getRefSpeedsRaw(double *spds) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getRefSpeesdRaw");}

    virtual bool getRefAccelerationRaw(int j, double *acc) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getRefAccelerationRaw");}

    virtual bool getRefAccelerationsRaw(double *accs) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getRefAccelerationsRaw");}

    virtual bool stopRaw(int j) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("stopRaw");}

    virtual bool stopRaw() YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("stopRaw");}
};

/**
 * Stub implementation of IEncodersRaw interface.
 * Inherit from this class if you want a stub implementation
 * of methods in IPositionControlRaw. This class allows to
 * gradually implement an interface; you just have to implement
 * functions that are useful for the underlying device.
 * Another way to see this class is as a means to convert
 * compile time errors in runtime errors.
 *
 * If you use this class please be aware that the device
 * you are wrapping might not function properly because you
 * missed to implement useful functionalities.
 *
 */
class YARP_dev_API yarp::dev::StubImplEncodersRaw: public IEncodersRaw
{
private:
    /**
     * Helper for printing error message, see below.
     * Implemented in ControlBoardInterfacesImpl.cpp.
     */
    bool NOT_YET_IMPLEMENTED(const char *func=0);

public:
    virtual ~StubImplEncodersRaw(){}

    virtual bool getAxes(int *ax) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getAxes");}

    virtual bool resetEncoderRaw(int j) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("resetEncoderRaw");}

    virtual bool resetEncodersRaw() YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("resetEncodersRaw");}

    virtual bool setEncoderRaw(int j, double val) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("setEncoderRaw");}

    virtual bool setEncodersRaw(const double *vals) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("setEncodersRaw");}

    virtual bool getEncoderRaw(int j, double *v) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getEncoderRaw");}

    virtual bool getEncodersRaw(double *encs) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getEncodersRaw");}

    virtual bool getEncoderSpeedRaw(int j, double *sp) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getEncoderSpeedRaw");}

    virtual bool getEncoderSpeedsRaw(double *spds) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getEncoderSpeedsRaw");}

    virtual bool getEncoderAccelerationRaw(int j, double *spds) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getEncoderAccelerationRaw");}

    virtual bool getEncoderAccelerationsRaw(double *accs) YARP_OVERRIDE
    {return NOT_YET_IMPLEMENTED("getEncoderAccelerationsRaw");}
};

#endif // YARP_DEV_IMPLEMENTCONTROLBOARDINTERFACES_H
