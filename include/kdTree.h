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
      m_rightNode(0)
    {}
    Node(const AABB& _bbox)
    : m_box( _bbox ),
      m_leftNode( 0 ),
      m_rightNode( 0 )
    {}
    ~Node() {}
    bool IsLeaf() const { if ( (m_leftNode ==0) && (m_rightNode==0) ) return true; else return false;}
    std::vector<const T*> m_list;
    AABB m_box;
    Node<T>* m_leftNode;
    Node<T>* m_rightNode;
};
//------------------------------------------------------------------------------
template <class T>
class KdTree
{
public:
    KdTree( uint32_t _num, const Matrix* _matrix, const std::vector<T>& _list = std::vector<T>(0) );
    ~KdTree()
    {
        DeleteBranch( m_root );
    }
    void Init();
    void AddData(const T& _data) { m_data.push_back(_data); };
    void DeleteBranch( Node<T>* _node )
    {
        if ( _node->m_leftNode!=0 )
            DeleteBranch( _node->m_leftNode );
        if ( _node->m_rightNode!=0 )
            DeleteBranch( _node->m_rightNode );
        delete _node;
    }
    void BuildTree( Node<T>* _node, uint32_t _depth );
    bool Intersect( const Node<T>* _node, const Ray& _ray, Intersection& o_intersection ) const;
    Node<T>* m_root;

//private:
    uint32_t m_leastObjNum;
    const Matrix* m_transform;
    std::vector<T> m_data;
};
//------------------------------------------------------------------------------
template <class T>
KdTree<T>::KdTree( uint32_t _num, const Matrix* _matrix, const std::vector<T>& _list )
: m_leastObjNum ( _num ),
  m_transform( _matrix ),
  m_data( _list )
{
    m_root = new Node<T>();
}
//------------------------------------------------------------------------------
template <class T>
void KdTree<T>::Init()
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
        if( ptr->Min().x() < xmin)
            xmin = ptr->Min().x();
        if( ptr->Max().x() > xmax)
            xmax = ptr->Max().x();
        if( ptr->Min().y() < ymin)
            ymin = ptr->Min().y();
        if( ptr->Max().y() > ymax)
            ymax = ptr->Max().y();
        if( ptr->Min().z() < zmin)
            zmin = ptr->Min().z();
        if( ptr->Max().z() > zmax)
            zmax = ptr->Max().z();
        m_root->m_list.push_back( ptr );
        ++iter;
    }
    xmin = xmin - EPSILON;
    ymin = ymin - EPSILON;
    zmin = zmin - EPSILON;
    xmax = xmax + EPSILON;
    ymax = ymax + EPSILON;
    zmax = zmax + EPSILON;
    m_root->m_box = AABB( xmin, ymin, zmin, xmax, ymax, zmax) ;
}
//------------------------------------------------------------------------------
template <class T>
void KdTree<T>::BuildTree( Node<T>* _node, uint32_t _depth)
{
    //std::cout<<"\n"<<"depth=========================== "<<_depth<<"\n";
    //std::cout<<"object number "<< _node->m_list.size()<<"\n";
    if( (_depth < 5) && (_node->m_list.size() > 50) )//m_leastObjNum ))
    {
        uint32_t axis = _depth%3;
        //get the centre of the box as median
        float splitPos = ( _node->m_box.Min()[axis] + _node->m_box.Max()[axis] ) /2.0;
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
        leftBox.SetMax( axis, splitPos );
        rightBox.SetMin( axis, splitPos );
        _node->m_leftNode = new Node<T>( leftBox );
        _node->m_rightNode = new Node<T>( rightBox );
        //add object to new _node
        typename std::vector<const T*>::const_iterator iter = _node->m_list.begin();
        while(iter!=_node->m_list.end())
        {
            if( (*iter)->Max()[axis] < splitPos || (*iter)->Min()[axis] < splitPos )
            {
                _node->m_leftNode->m_list.push_back(*iter);
            }
            if( (*iter)->Max()[axis] > splitPos || (*iter)->Min()[axis] > splitPos )
            {
                _node->m_rightNode->m_list.push_back(*iter);
            }
            ++iter;
        }

        for( uint32_t i=0; i< _node->m_list.size(); ++i)
        {
            //std::cout<< _node->m_list[i]->s_id <<" ";
        }

        _depth+=1;
        BuildTree( _node->m_leftNode, _depth );
        BuildTree( _node->m_rightNode, _depth );
        _node->m_list.clear();
    }
}
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
        if ( ( _node->m_box*(*m_transform) ).Intersect ( _ray, dis ) )
        {
            Intersection intersection;
            for( uint32_t i=0; i< _node->m_list.size(); ++i )
            {
                Intersection tmp;
                if ( ( ( *_node->m_list[i] ) * (*m_transform) ). Intersect ( _ray, tmp )
                     && ( tmp.RayParameter() < intersection.RayParameter() ) )
                    intersection = tmp;
            }
            if ( intersection.Intersected() )
            {
                o_intersection = intersection;
                return true;
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
        bool leftIntersected = ( _node->m_leftNode->m_box * (*m_transform) ).Intersect( _ray, disLeft );
        bool rightIntersected = ( _node->m_rightNode->m_box * (*m_transform) ).Intersect( _ray, disRight );
        //both have intersection
        if ( leftIntersected && rightIntersected )
        {
            //intersect the closer one
            //if no intersection otherwise intersect the further one
            if ( disLeft < disRight )
            {
                bool intersected = Intersect ( _node->m_leftNode, _ray, o_intersection );
                if( intersected )
                    return true;
                else return Intersect ( _node->m_rightNode, _ray, o_intersection );
            }
            else
            {
                bool intersected = Intersect ( _node->m_rightNode, _ray, o_intersection );
                if( intersected )
                    return true;
                else return Intersect ( _node->m_leftNode, _ray, o_intersection );
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
}//end of namespace
#endif
