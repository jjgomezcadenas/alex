#ifndef VECTORS_H
#define VECTORS_H

#include <alex/GDefs.h>
#include <alex/TDefs.h>

namespace alex {
  std::string PrintTVector3(TVector3 t);
  std::string PrintTLorentzVector(TLorentzVector t);

  template< typename T>
  std::string  PrintVector (const T& vd, size_t dim)
  {
    std::ostringstream s;
    //s << std::endl;
    s<<"(";
    for (int i=0; i < dim-1; i++)
      s<< vd[i] << "," ;
    s <<vd[dim-1] <<")" << std::ends;
    return s.str();
  }

  template< typename T>
  std::string VPrint(const std::vector<T>& vd)
  {
    return PrintVector(vd,vd.size());
  }
    
  template< typename T>
  std::string PrintMatrix(const T& M, size_t id, size_t jd)
  {
    std::ostringstream s;
    //s << std::endl;
    s<<"[" <<std::endl;
    for (int i=0; i < id; i++)
    {
      s<<"("<<M[i][0]<<",";
      for (int j=1; j < jd-1; j++)
        s<< M[i][j] << "," ;
      s <<M[i][jd-1] <<")" << std::endl;
    }
    s<<"]"<< std::ends;
    return s.str();
  }

  template< typename T>
  T CopyMatrix(const T& M, size_t id, size_t jd)
  {
    T C;
    for (int i=0; i < id; i++)
      for (int j=1; j < jd; j++)
        C[i][j]=M[i][j];

    return C;
  }

  template< typename T>
  T CopyVector(const T& V, size_t id)
  {
    T C;
    for (int i=0; i < id; i++)
        C[i]=V[i];

    return C;
  }

  template< typename T>
  typename T::value_type Sum(const T& v) 
  {
    return std::accumulate(v.begin(), v.end(), 0, std::plus<typename T::value_type>());
  }

template< typename T>
  void VPointerCopy(std::vector<T*> vfrom, std::vector<T*>& vtarget) //
  {
    for (size_t i=0; i < vfrom.size(); ++i)
    {
      T* p = new T(*vfrom[i]);
      vtarget.push_back(p);
    }
  }

  template< typename T>
  std::vector<T*> VClone(std::vector<T*> vfrom) //
  {
    std::vector<T*> vtarget;
    vtarget.reserve(vfrom.size());
    VPointerCopy(vfrom, vtarget);
    return vtarget;
  }

  template< typename T>
  std::vector<const T*> VCloneConstant(std::vector<T*> vfrom) 
  {
    std::vector<const T*> pos;
    pos.reserve(vfrom.size());
    for (size_t i=0; i < vfrom.size(); ++i)
    {
      const T* p = new T(*vfrom.at(i));
      pos.push_back(p);
    }
      return pos;
  }
  template< typename T>
  std::vector<T> VCopy(const std::vector<T>& vfrom)
  {
    std::vector<T> pos;
    pos.reserve(vfrom.size());
    for (size_t i=0; i < vfrom.size(); ++i)
      pos.push_back(vfrom[i]);

    return pos;
  }
  template< typename T>
  std::vector<const T> VCopyConstant(const std::vector<T>& vfrom)
  {
    std::vector<const T> pos;
    pos.reserve(vfrom.size());
    for (size_t i=0; i < vfrom.size(); ++i)
      pos.push_back(vfrom[i]);

    return pos;
  }

  template< typename T>
  void VDelete(std::vector<T*> v) //
  {
    for (size_t i=0; i < v.size(); ++i)
    {
      delete v[i];
    }
  }

} // namespace 

#endif // VECTORS_H
