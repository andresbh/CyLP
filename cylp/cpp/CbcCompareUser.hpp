// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
#ifndef CbcCompareUser_H
#define CbcCompareUser_H

//#define NPY_NO_DEPRECATED_API

#include "CbcNode.hpp"
#include "CbcCompareBase.hpp"
#include "ICbcModel.hpp"
#include "ICbcNode.hpp"
#include "Python.h"
#include <numpy/arrayobject.h>

//class ICbcModel;



/* This is an example of a more complex rule with data
   It is default after first solution
   If weight is 0.0 then it is computed to hit first solution
   less 2%
*/
class CbcCompareUser  : public CbcCompareBase {
public:
  // Default Constructor
  CbcCompareUser (PyObject* obj, runTest_t runTest,
                    runNewSolution_t runNewSolution,
                    runEvery1000Nodes_t runEvery1000Nodes) ;
  // Constructor with weight
  //CbcCompareUser (double weight);

  // Copy constructor
  CbcCompareUser ( const CbcCompareUser &rhs);

  // Assignment operator
  CbcCompareUser & operator=( const CbcCompareUser& rhs);

  /// Clone
  virtual CbcCompareBase * clone() const;

  ~CbcCompareUser() ;
  /* This returns true if weighted value of node y is less than
     weighted value of node x */
  // Returns true if y better than x
  virtual bool test (CbcNode * x, CbcNode * y) ;
  /// This is alternate test function
  virtual bool alternateTest (CbcNode * x, CbcNode * y);
  // This allows method to change behavior as it is called
  // after each solution
  virtual bool newSolution(CbcModel * model,
			   double objectiveAtContinuous,
			   int numberInfeasibilitiesAtContinuous) ;
  /// Returns true if wants code to do scan with alternate criterion
  virtual bool fullScan() const;
  // This allows method to change behavior
  // Return true if want tree re-sorted
  virtual bool every1000Nodes(CbcModel * model,int numberNodes);

  /* if weight == -1.0 then depth first (before solution)
     if -2.0 then do breadth first just for first 1000 nodes
  */
  inline double getWeight() const
  { return weight_;}
  inline void setWeight(double weight)
  { weight_ = weight;}
protected:
  // Weight for each infeasibility
  double weight_;
  // Weight for each infeasibility - computed from solution
  double saveWeight_;
  // Number of solutions
  int numberSolutions_;
  // count
  mutable int count_;
  // Tree size (at last check)
  int treeSize_;
  runTest_t runTest;
  runEvery1000Nodes_t runEvery1000Nodes;
  runNewSolution_t runNewSolution;
  PyObject* obj;
};
#endif
