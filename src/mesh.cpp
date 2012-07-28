#include "mesh.h"
#include "float.h"
namespace rayTracer
{
//------------------------------------------------------------------------------
Mesh::~Mesh ()
{}
//------------------------------------------------------------------------------
void Mesh::SetMaterial( const Material* _pMaterial )
{
	m_pMaterial = _pMaterial;
	for(uint32_t i=0; i< m_tree.m_data.size(); ++i )
	{
		m_tree.m_data[i].SetMaterial(_pMaterial);
	}
}
//------------------------------------------------------------------------------
Mesh::Mesh ( const Vector& _pos, const std::string& _fileName, Material* _pMaterial )
: m_tree(10)
{
    ObjLoader obj;
	obj.ParseFile (_fileName);
	Translate(_pos);
	m_pMaterial = _pMaterial;

	uint32_t size = obj.GetVertexArray().size();
	m_tree.m_data.reserve(size);
	for(uint32_t i=0; i< size; i+=3 )
	{
		if ( obj.GetTextureArray().size()!=0 )
		m_tree.m_data.push_back( Triangle( obj.GetVertexArray()[i],
										   obj.GetVertexArray()[i+1],
										   obj.GetVertexArray()[i+2],
										   obj.GetNormalArray()[i],
										   obj.GetNormalArray()[i+1],
										   obj.GetNormalArray()[i+2],
										   obj.GetTextureArray()[i],
										   obj.GetTextureArray()[i+1],
										   obj.GetTextureArray()[i+2],
										   m_pMaterial,
										   (uint32_t)(i/3.0)) );
	}
	m_tree.CreateBBox();
}
//------------------------------------------------------------------------------
void Mesh::ToCameraSpace( const Matrix& _transform)
{
	m_tree.Transform( _transform );
	uint32_t depth=0;
	m_tree.BuildTree( m_tree.m_root, depth );
}
//------------------------------------------------------------------------------
bool Mesh::Intersect ( const Ray& _ray, Intersection& o_intersection ) const
{
	//intersect kd tree
	bool result = m_tree.m_root->Intersect(_ray, o_intersection );
	//bool result = m_tree.Intersect(m_tree.m_root, _ray, o_intersection );
	return result;
}
}//end of namespace
