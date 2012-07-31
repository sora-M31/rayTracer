#ifndef _KD_TREE_H_
#define _KD_TREE_H_
#include "AABB.h"
#include "util.h"

namespace rayTracer
{
//node class
template <typename T>
class Node
{
public:
    Node()
    : m_leftNode(0),
      m_rightNode(0),
	  m_split(0)
    {}
    Node(const AABB& _bbox)
    : m_box( _bbox ),
      m_leftNode( 0 ),
      m_rightNode( 0 ),
	  m_split(0)
    {}
    ~Node() {}
    bool IsLeaf() const {  return ( m_leftNode ==0 ) && ( m_rightNode==0 ); }
	bool Intersect( const Ray& _ray, Intersection& o_intersection) const;

    std::vector<const T*> m_list;
    AABB m_box;
    Node<T>* m_leftNode;
    Node<T>* m_rightNode;
	float m_split;
	uint32_t m_axis;
};
template <class T>
//------------------------------------------------------------------------------
bool Node<T>::Intersect( const Ray& _ray, Intersection& o_intersection ) const
{
    if( IsLeaf() )
    {
		Intersection intersection;
		for( uint32_t i=0; i< m_list.size(); ++i )
		{
			Intersection tmp;
			if (  m_list[i]->Intersect ( _ray, tmp )
				&& tmp.Distance() < intersection.Distance()  )
			{
					intersection = tmp;
			}
		}
		//if there is any return the closest intersection that is in the box
		if ( !intersection.Intersected() )
		{
			return false;
		}

		Vector dis1 = intersection.Position() - m_box.Min();
		Vector dis2 = m_box.Max() - intersection.Position();
		float epsilon = 0;
		if(    dis1.x() > epsilon
			&& dis1.y() > epsilon
			&& dis1.z() > epsilon
			&& dis2.x() > epsilon
			&& dis2.y() > epsilon
			&& dis2.z() > epsilon
			)
		{
			o_intersection = intersection;
			return true;
		}
		else
			return false;
    }
    //if node is not a leaf node
    else
    {
		float tMin, tMax;
		//not intersected with bounding box
		if( !m_box.Intersect( _ray, tMin, tMax ) )
		{
			return false;
		}
		float rayDir = _ray.Direction()[m_axis];
		float tSplit = (m_split - _ray.Origin()[m_axis])/_ray.Direction()[m_axis] ;

		Node<T>* near(0);
		Node<T>* far(0);
#if 1
		//origin on "left " of m_splitPos
		if( _ray.Origin()[m_axis] < m_split )
		{
			near = m_leftNode;
			far = m_rightNode;
		}
		//origin on "right" of m_splitPos
		else if ( _ray.Origin()[m_axis] > m_split )
		{
			near = m_rightNode;
			far = m_leftNode;
		}
		//origin on the spliting plane
		else
		{
			if( rayDir <= 0)
			{
				near = m_leftNode;
				far = m_rightNode;
			}
			else
			{
				near = m_rightNode;
				far = m_leftNode;
			}
		}

		//split is infinit
		if( rayDir == 0 )
		{
			if ( m_split == _ray.Direction()[m_axis] )
			{
				bool result = near->Intersect ( _ray, o_intersection );
				if( !result )
					result = far->Intersect ( _ray, o_intersection );
				return result;
			}
			else
			{
				return near->Intersect ( _ray, o_intersection );
			}
		}
		else if ( tSplit > tMax )
		{
			return near->Intersect( _ray, o_intersection );
		}
		else if ( tSplit >= tMin && tSplit <= tMax )
		{
			bool result = near->Intersect ( _ray, o_intersection );
			if( !result )
				result = far->Intersect ( _ray, o_intersection );
			return result;
		}
		else if ( tSplit>0 &&tSplit < tMin )
		{
			return far->Intersect( _ray, o_intersection );
		}
		else if( tSplit <= 0)
		{
			return near->Intersect( _ray, o_intersection );
		}
#endif
#if 0
		float epsilon = 0.0001;
		float originSplitDis = _ray.Origin()[m_axis] - m_split;
		//ray origin lie on spliting plane
		//ray origin on right of splitting plane
		if  ( originSplitDis > 0 )
		{
			near = m_rightNode;
			far = m_leftNode;
		}
		//ray origin on left of splitting plane
		else if  ( originSplitDis <= 0 )
		{
			near = m_leftNode;
			far = m_rightNode;
		}
		//parallel
		if( fabs(_ray.Direction()[m_axis]) < epsilon )
		{
#if 0
			if ( fabs(originSplitDis < epsilon ) )
			{
				bool result = near->Intersect ( _ray, o_intersection );
				if( !result )
					result = far->Intersect ( _ray, o_intersection );
				return result;
			}
			else
			{
				return near->Intersect ( _ray, o_intersection );
			}
#endif
		}
		if ( tSplit > tMin && tSplit < tMax )
		{
			bool result = near->Intersect ( _ray, o_intersection );
			if( !result )
				result = far->Intersect ( _ray, o_intersection );
			return result;
		}
		else if ( tSplit > tMax )
		{
			return near->Intersect( _ray, o_intersection );
		}
		else if ( tSplit>0 && tSplit < tMin )
		{
			return far->Intersect( _ray, o_intersection );
		}
		else if ( tSplit<=0 && tSplit < tMin )
		{
			return near->Intersect( _ray, o_intersection );
		}
#endif
	}
}
//------------------------------------------------------------------------------
template <class T>
class KdTree
{
public:
	// --------------------------------------------------------------------------
	/// \brief 
	/// \param _maxNum maximum object allowed in each leaf node
	/// \param _list polygon data array
    KdTree( uint32_t _maxNum, const std::vector<T>& _list = std::vector<T>(0) );
    ~KdTree()
    {
        DeleteBranch( m_root );
    }
	// --------------------------------------------------------------------------
	/// \brief create bounding box for the tree
    void CreateBBox();
    //void AddData( const T& _data ) { m_data.push_back(_data); };
    void DeleteBranch( Node<T>* _node )
    {
        if ( _node->m_leftNode!=0 )
            DeleteBranch( _node->m_leftNode );
        if ( _node->m_rightNode!=0 )
            DeleteBranch( _node->m_rightNode );
        delete _node;
    }
    void Transform( const Matrix& _transform );
	// --------------------------------------------------------------------------
	/// \brief build tree recursively
	/// \param _node
	/// \param _depth
    void BuildTree( Node<T>* _node, uint32_t _depth );
    //bool Intersect( const Node<T>* _node, const Ray& _ray, Intersection& o_intersection ) const;

    Node<T>* m_root;
    uint32_t m_leastObjNum;
    std::vector<T> m_data;
    std::vector<T> m_dataTransformed;
    AABB m_bbox;
};
//------------------------------------------------------------------------------
template <class T>
KdTree<T>::KdTree( uint32_t _num, const std::vector<T>& _list )
: m_leastObjNum ( _num ),
  m_data( _list )
{
    m_root = new Node<T>();
}
//------------------------------------------------------------------------------
template <class T>
void KdTree<T>::CreateBBox()
{
    //decide the boundary of the initial box
    float xmin = FLT_MAX;
    float xmax = -FLT_MAX;
    float ymin = FLT_MAX;
    float ymax = -FLT_MAX;
    float zmin = FLT_MAX;
    float zmax = -FLT_MAX;
    typename std::vector< T >::const_iterator iter = m_data.begin();
    while( iter != m_data.end() )
    {
        const T* ptr = &(*iter);

        if( ptr->Min().x() < xmin) xmin = ptr->Min().x();
        if( ptr->Min().z() < zmin) zmin = ptr->Min().z();
        if( ptr->Min().y() < ymin) ymin = ptr->Min().y();

        if( ptr->Max().x() > xmax) xmax = ptr->Max().x();
        if( ptr->Max().y() > ymax) ymax = ptr->Max().y();
        if( ptr->Max().z() > zmax) zmax = ptr->Max().z();
        ++iter;
    }
	float epsilon = 0.00001;
    xmin = xmin - epsilon;
    ymin = ymin - epsilon;
    zmin = zmin - epsilon;
    xmax = xmax + epsilon;
    ymax = ymax + epsilon;
    zmax = zmax + epsilon;
    m_bbox = AABB( xmin, ymin, zmin, xmax, ymax, zmax);
    m_root->m_box = m_bbox;
}
//------------------------------------------------------------------------------
template <class T>
void KdTree<T>::Transform(const Matrix& _transform)
{
	//another choice: transformed ray to local space
	//delete the old tree and prepare for building a new tree
	if( m_root->m_leftNode)
		DeleteBranch( m_root->m_leftNode );
	if( m_root->m_rightNode)
		DeleteBranch( m_root->m_rightNode );

    m_dataTransformed.clear();
    m_root->m_list.clear();
    m_dataTransformed.reserve( m_data.size() );
    for( uint32_t i=0; i< m_data.size(); ++i )
    {
        m_dataTransformed.push_back (m_data[i] * ( _transform ));
        m_root->m_list.push_back( &m_dataTransformed[i] );
    }
    m_root->m_box = m_bbox.Update( _transform );
}
//------------------------------------------------------------------------------
template <class T>
void KdTree<T>::BuildTree( Node<T>* _node, uint32_t _depth)
{
    if( (_depth < 20) && (_node->m_list.size() > m_leastObjNum) )
    {
        float axis = _depth%3;
		_node->m_axis = axis;
        //get the centre of the box as median
        _node->m_split = ( _node->m_box.Min()[axis] + _node->m_box.Max()[axis] ) /2.0;
#if 0
        //get average position as median to get a ballanced tree
        while( iter!=_node->m_list.end())
        {
            splitPos+= (*iter)->Position()[axis];
        }
        splitPos/=_node->m_list.size();
#endif
        //divide space in two
        AABB leftBox = _node->m_box;
        AABB rightBox = _node->m_box;
        leftBox.SetMax( axis, _node->m_split );
        rightBox.SetMin( axis, _node->m_split );
        _node->m_leftNode = new Node<T>( leftBox );
        _node->m_rightNode = new Node<T>( rightBox );
        //add object to new _node
        typename std::vector<const T*>::const_iterator iter = _node->m_list.begin();
        while(iter!=_node->m_list.end())
        {
			//todo: comparison template for other type of object
            if((*iter)->Min()[axis] < _node->m_split)
            {
                _node->m_leftNode->m_list.push_back(*iter);
            }
            if( (*iter)->Max()[axis] > _node->m_split)
            {
                _node->m_rightNode->m_list.push_back(*iter);
            }
            ++iter;
        }
        _depth+=1;
        BuildTree( _node->m_leftNode, _depth );
        BuildTree( _node->m_rightNode, _depth );
        _node->m_list.clear();
    }
}
#if 0
template <class T>
//------------------------------------------------------------------------------
bool KdTree<T>::Intersect( const Node<T>* _node, const Ray& _ray, Intersection& o_intersection ) const
{
    //if node is leaf node
    if( _node->IsLeaf() )
    //check aabb box first
    //if intersect box, intersect all objects in the node
    //if there is any return the closest intersection
    {
        float dis;
        if ( ( _node->m_box ).Intersect ( _ray, dis ) )
        {
            Intersection intersection;
            for( uint32_t i=0; i< _node->m_list.size(); ++i )
            {
                Intersection tmp;
                if (  _node->m_list[i]->Intersect ( _ray, tmp )
					&& tmp.Distance() < intersection.Distance()  )
				{
						intersection = tmp;
				}
            }
            if ( intersection.Intersected() )
            {
				Vector dis1 = intersection.Position() - _node->m_box.Min();
				Vector dis2 = _node->m_box.Max() - intersection.Position();
				float epsilon = 0.0000001;
				if(    dis1.x() > epsilon
					&& dis1.y() > epsilon
					&& dis1.z() > epsilon
					&& dis2.x() > epsilon
					&& dis2.y() > epsilon
					&& dis2.z() > epsilon
					)
				{
					o_intersection = intersection;
                return true;
				}
				else return false;
            }
            else return false;
        }
        else return false;
    }
    //if node is not a leaf node
    else
    {
        float disLeft = FLT_MAX;
        float disRight = FLT_MAX;
        bool leftIntersected = ( _node->m_leftNode->m_box  ).Intersect( _ray, disLeft );
        bool rightIntersected = ( _node->m_rightNode->m_box ).Intersect( _ray, disRight );
        //both have intersection
        if ( leftIntersected && rightIntersected )
        {
            //intersect the closer one
            //if no intersection otherwise intersect the further one
            if ( disRight > disLeft )
            {
                bool intersected = Intersect ( _node->m_leftNode, _ray, o_intersection );
                if( intersected )
				{
					return true;
				}
                else
					return Intersect ( _node->m_rightNode, _ray, o_intersection );
            }
            else
            {
                bool intersected = Intersect ( _node->m_rightNode, _ray, o_intersection );
                if( intersected )
                    return true;
                else
					return Intersect ( _node->m_leftNode, _ray, o_intersection );
            }
        }
        //one of them have intersection
        else if ( leftIntersected && !rightIntersected )
        {
            return Intersect( _node->m_leftNode, _ray, o_intersection );
        }
        else if ( !leftIntersected && rightIntersected )
        {
            return Intersect( _node->m_rightNode, _ray, o_intersection );
        }
        //none has intersection
        else
            return false;
    }
}
#endif
}//end of namespace
#endif
