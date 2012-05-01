#ifndef _RAY_H_
#define _RAY_H_

#include "vector.h"

namespace rayTracer
{
class Material;
class Ray
{
public:
	Ray ( const Vector& _origin, const Vector& _direction, const Material* _pMaterial );
	Ray ( const Ray& ray );
	
	const Vector& Origin () const { return m_origin; }
	const Vector& Direction () const { return m_direction; }
	const Material* GetMaterial () const { return m_pMaterial; }
	Vector GetPosition ( float rayParameter ) const;
private:
	Vector m_origin;
	Vector m_direction;
	const Material* m_pMaterial;
};//end of class
}//end of namespace
#endif //end of define
