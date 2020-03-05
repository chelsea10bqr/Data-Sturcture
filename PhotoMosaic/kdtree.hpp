/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if(first[curDim]!=second[curDim]){
       return first[curDim]<second[curDim];
     }
     return first<second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double sum_c=0;
     double sum_p=0;
     for(int i =0;i<Dim;i++){
       sum_c = getDistance(currentBest,target);
       sum_p = getDistance(potential,target);
     }
     if(sum_c!=sum_p){
       return sum_p<sum_c;
     }
     return (potential<currentBest);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     points = newPoints;
     root = build(points,0,newPoints.size()-1,0);



}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   points = other.points;
   root = build(points,0,points.size()-1,0);

}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   if(this!=&rhs){
     Delete(this);
     points = rhs.points;
     root = build(rhs.points,0,rhs.points.size()-1,0);
   }

  return *this;
}

template <int Dim>
 typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::build(vector<Point<Dim>>& points,int begin,int end,int d){
    if((end-begin)<0){
      return NULL;
    }
    int mid =(begin+end)/2;
    median(points,begin,end,mid,d);
    KDTreeNode* cur= new KDTreeNode(points[mid]);
    d = d+1;
    if(d==Dim){
      d=0;
    }
    cur->left = build(points,begin,mid-1,d);
    cur->right = build(points,mid+1,end,d);
    return cur;


 }

 template <int Dim>
 void KDTree<Dim>::median(vector<Point<Dim>>& points,int begin,int end,int mid,int d){
   if(begin==end){
     return;
   }
   int mid_1 = partition(points,begin,end,mid,d);
   if(mid==mid_1){
     return;
   }else if(mid<mid_1){
     median(points,begin,mid_1-1,mid,d);
     return;
   }else{
     median(points,mid_1+1,end,mid,d);
     return;
   }
 }


template <int Dim>
void KDTree<Dim>::swap(vector<Point<Dim>>& points,int one, int two){
  Point<Dim> temp = points[one];
  points[one] = points[two];
  points[two] = temp;
}

template<int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& points,int begin, int end,int cen,int d){
 Point<Dim> temp = points[cen];
 swap(points,cen,end);
 int it = begin;
 for(int i = begin;i<end;i++){
   if(points[i][d]==temp[d]){
     if(points[i]<temp){
       swap(points,it,i);
       it++;
     }
   }
 if(points[i][d]<temp[d]){
   swap(points,it,i);
   it++;
 }
}
swap(points,end,it);
return it;
}

template<int Dim>
void KDTree<Dim>::Delete(KDTreeNode* r){
  if(r!=NULL){
    Delete(r->left);
    Delete(r->right);
    delete r;
  }

}
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   Delete(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
     /**
     * @todo Implement this function!
     */


    return findNearestHelper(0,0,points.size()-1,points[(points.size()-1)/2],query);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestHelper(int curDim,int begin, int end,const Point<Dim>& currentBest,const Point<Dim>& query)const{
   int mid = (begin+end)/2;
   Point<Dim> best = currentBest;
   bool t_left = true;
   Point<Dim> temp = points[mid];

   if(begin == end){
     if(shouldReplace(query,currentBest,points[begin])){
       best = points[begin];
       return best;
     }
     best = currentBest;
     return best;
   }

   if(smallerDimVal(points[mid],query,curDim)){
     if(end>mid){
       best = findNearestHelper((curDim+1)%Dim,mid+1,end,currentBest,query);
       t_left = false;
     }
   }
  if(smallerDimVal(query,points[mid],curDim)){
    if(begin<mid){
      best = findNearestHelper((curDim+1)%Dim,begin,mid-1,currentBest,query);
      t_left = true;
    }
  }
  if(shouldReplace(query,best,points[mid])){
    best = points[mid];
  }
  int r = 0;
  for(int i = 0;i<Dim;i++){
    r = r+(query[i]-best[i])*(query[i]-best[i]);
  }
  if((temp[curDim]-query[curDim])*(temp[curDim]-query[curDim])<=r){
    if(t_left&&end>mid){
      best = findNearestHelper((curDim+1)%Dim,mid+1,end,best,query);
    }else if(!t_left&& begin<mid){
      best = findNearestHelper((curDim+1)%Dim,begin,mid-1,best,query);
  }
}
  return best;

}


template <int Dim>
double KDTree<Dim>::getDistance(const Point<Dim> &first, const Point<Dim>& second) const{
  double sum = 0;
  for(int i =0;i<Dim;i++){
    sum = sum+(first[i]-second[i])*(first[i]-second[i]);
  }
  return sum;
}
