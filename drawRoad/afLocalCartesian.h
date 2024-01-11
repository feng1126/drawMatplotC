#ifndef _AF_LOCALCARTESIAN_H_
#define _AF_LOCALCARTESIAN_H_
#include <math.h>

/**
 * \brief Local cartesian coordinates
 *
 * Convert between geodetic coordinates latitude = \e lat, longitude = \e
 * lon, height = \e h (measured vertically from the surface of the ellipsoid)
 * to local cartesian coordinates (\e x, \e y, \e z).  The origin of local
 * cartesian coordinate system is at \e lat = \e lat0, \e lon = \e lon0, \e h
 * = \e h0. The \e z axis is normal to the ellipsoid; the \e y axis points
 * due north.  The plane \e z = - \e h0 is tangent to the ellipsoid.
 *
 * The conversions all take place via geocentric coordinates using a
 * Geocentric object (by default Geocentric::WGS84()).
 *
 * Example of use:
 * \include example-LocalCartesian.cpp
 *
 * <a href="CartConvert.1.html">CartConvert</a> is a command-line utility
 * providing access to the functionality of Geocentric and LocalCartesian.
 **********************************************************************/

#define PI 3.141592653589793
#define EARTH_RADIUS 6378137.0 // meter
#define FLATRATE (1.0 / 298.257223565)
#define ECCENTRICITY (FLATRATE * (2 - FLATRATE))
#define  dim2_  (9) 

class LocalCartesian
{
private:
    typedef double real;

    real _lon0, _lat0, _h0;
    real _x0, _y0, _z0, _r[dim2_];

public:
    LocalCartesian();
    ~LocalCartesian();
    void Release();

    /**
     * Reset the origin.
     *
     * @param[in] lon0 longitude at origin (degrees).
     * @param[in] lat0 latitude at origin (degrees).
     * @param[in] h0 height above ellipsoid at origin (meters); default 0.
     *
     * \e lat0 should be in the range [&minus;90&deg;, 90&deg;].
     **********************************************************************/
    void Reset(real lon0, real lat0, real h0);
    void Rotation(real sphi, real cphi, real slam, real clam, real M[dim2_]);

    /**
     * Convert from geodetic to local cartesian coordinates.
     *
     * @param[in] lon longitude of point (degrees).
     * @param[in] lat latitude of point (degrees).
     * @param[in] h height of point above the ellipsoid (meters).
     * @param[out] x local cartesian coordinate (meters).
     * @param[out] y local cartesian coordinate (meters).
     * @param[out] z local cartesian coordinate (meters).
     *
     * \e lat should be in the range [&minus;90&deg;, 90&deg;].
     **********************************************************************/
    void LLAToEgo(real lon, real lat, real h, float head, real& x, real& y, real& z);
    void LLAToECEF(real lon, real lat, real h, real& x, real& y, real& z);
};

#endif // GEOGRAPHICLIB_LOCALCARTESIAN_HPP
