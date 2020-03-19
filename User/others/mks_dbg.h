#ifndef _MKS_DBG_H_
#define _MKS_DBG_H_

#define MKS_DEBUG

#ifdef MKS_DEBUG
#define MKS_DBG(X,...) printf(X,##__VA_ARGS__)
#else
#define MKS_DBG(...)
#endif



#endif

