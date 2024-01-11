#include "afLocalCartesian.h"


using namespace std;

LocalCartesian::LocalCartesian()
{
    _lon0 = 0;
    _lat0 = 0;
    _h0 = 0;
    _x0 = 0;
    _y0 = 0;
    _z0 = 0;
    for (unsigned int i = 0; i < dim2_; i++)
    {
        _r[i] = 0;
    }
}

LocalCartesian::~LocalCartesian()
{
}

void LocalCartesian::Release()
{
}

// Set coordinate system origin, and calculate coordinate transformation matrix from ECEF to ENU
void LocalCartesian::Reset(real lon0, real lat0, real h0)
{
    h0 = 0.0;
    LLAToECEF(lon0, lat0, h0, _x0, _y0, _z0);
    real sphi, cphi, slam, clam;
    sphi = sin(lat0 / 180.0 * PI);
    cphi = cos(lat0 / 180.0 * PI);
    slam = sin(lon0 / 180.0 * PI);
    clam = cos(lon0 / 180.0 * PI);
    Rotation(sphi, cphi, slam, clam, _r);
}

void LocalCartesian::Rotation(real sphi, real cphi, real slam, real clam, real M[dim2_])
{
    // This rotation matrix is given by the following quaternion operations
    // qrot(lam, [0,0,1]) * qrot(phi, [0,-1,0]) * [1,1,1,1]/2
    // or
    // qrot(pi/2 + lam, [0,0,1]) * qrot(-pi/2 + phi , [-1,0,0])
    // where
    // qrot(t,v) = [cos(t/2), sin(t/2)*v[1], sin(t/2)*v[2], sin(t/2)*v[3]]

    // Local X axis (east) in geocentric coords
    M[0] = -slam;
    M[3] = clam;
    M[6] = 0;
    // Local Y axis (north) in geocentric coords
    M[1] = -clam * sphi;
    M[4] = -slam * sphi;
    M[7] = cphi;
    // Local Z axis (up) in geocentric coords
    M[2] = clam * cphi;
    M[5] = slam * cphi;
    M[8] = sphi;
}

void LocalCartesian::LLAToEgo(real lon, real lat, real h, float head, real& x, real& y, real& z)
{
    h = 0.0;
    // step 1: LLA to ECEF
    real xc, yc, zc;
    LLAToECEF(lon, lat, h, xc, yc, zc);
    xc -= _x0;
    yc -= _y0;
    zc -= _z0;

    // LOGPrint("LLAToEgo 0 : %0.10f, %0.10f, %0.10f ,%0.10f, %0.10f, %0.10f \n", lon, lat, h, xc, yc, zc);

     // setp 2: ECEF to ENU
    real x_enu, y_enu, z_enu;
    x_enu = _r[0] * xc + _r[3] * yc + _r[6] * zc;
    y_enu = _r[1] * xc + _r[4] * yc + _r[7] * zc;
    z_enu = _r[2] * xc + _r[5] * yc + _r[8] * zc;

    // LOGPrint("LLAToEgo 1 : %0.10f, %0.10f, %0.10f ,%0.10f \n", x_enu, y_enu, z_enu);
     //LOGPrint("LLAToEgo 2 : %0.10f, %0.10f, %0.10f ,%0.10f, %0.10f, %0.10f ,%0.10f, %0.10f, %0.10f \n", _r[0], _r[1], _r[2], _r[3], _r[4], _r[5], _r[6], _r[7], _r[8]);

     // step 3: ENU(Localization system) to EGO(front-left-up) , rotate the heading angle around the Z axis
     // heading angle : 0:the East, 90:the North, -90:the negative North
     // head = head / 180 * PI;
    real x_ego, y_ego, z_ego;
    x_ego = x_enu * cos(head / 180.0 * PI) + y_enu * sin(head / 180.0 * PI);
    y_ego = -x_enu * sin(head / 180.0 * PI) + y_enu * cos(head / 180.0 * PI);
    z_ego = z_enu;

    //LOGPrint("LLAToEgo 3 : %0.10f, %0.10f, %0.10f ,%0.10f \n", head / 180.0 * PI, x_ego, y_ego, z_ego);

    // Final step: Combine motion compensation
    // DeadReckonResults* pDR_Results = afGetDRResult();
    x = x_ego; // - pDR_Results->delta_x;
    y = y_ego; // - pDR_Results->delta_y;
    z = z_ego;
}

void LocalCartesian::LLAToECEF(real lon, real lat, real h, real& x, real& y, real& z)
{
    real sphi, cphi, slam, clam;
    sphi = sin(lat / 180.0 * PI);
    cphi = cos(lat / 180.0 * PI);
    slam = sin(lon / 180.0 * PI);
    clam = cos(lon / 180.0 * PI);
    real n = EARTH_RADIUS / sqrt(1 - ECCENTRICITY * sphi * sphi);
    z = ((1 - FLATRATE) * (1 - FLATRATE) * n + h) * sphi;
    x = (n + h) * cphi;
    y = x * slam;
    x *= clam;
}
