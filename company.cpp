#include "company.h"

CompanyTracker::CompanyTracker (int n)
  // initializes the tracker with n students and their 1-person companies
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; i++){
      companies[i] = new Company ();
  }

}

CompanyTracker::~CompanyTracker ()
  // deallocates all dynamically allocated memory
{
  for(int i=0; i<numCompanies; i++){
    delete [] companies[i];
  }
  delete [] companies;
}           

void CompanyTracker::merge (int i, int j)
  /* Merges the largest companies containing students i and j,
     according to the rules described above.
     That is, it generates a new Company object which will
     become the parent company of the largest companies currently
     containing students i and j.
     If i and j already belong to the same company (or are the same),
     merge doesn't do anything.
     If either i or j are out of range, merge doesn't do anything. */
{
  if(i < 0 || j < 0 || i >= numCompanies || j >= numCompanies){
    // either i or j is out of range
    return;
  }

  if(i == j){
    // i and j are the same
    return;
  }

  if(companies[i]->parent == companies[j]->parent && companies[i]->parent != nullptr){
    // i and j have the same parent company (doesn't apply when both are NULL)
    return;
  }

    Company* temp1 = largestParent(companies[i]);
    Company* temp2 = largestParent(companies[j]);
    Company* tempParent = new Company(temp1, temp2);
    temp1->parent = tempParent;
    temp2->parent = tempParent;

  return;
}

void CompanyTracker::split (int i)
  /* Splits the largest company that student i belongs to,
     according to the rules described above.
     That is, it deletes that Company object, and makes sure that
     the two subcompanies have no parent afterwards.
     If i's largest company is a 1-person company, split doesn't do anything.
     If i is out of range, split doesn't do anything. */
{
  if(companies[i]->parent == nullptr){
    // i's largest company is a 1-person company
    return;
  }

  if(i < 0 || i >= numCompanies){
    // i is out of range
    return;
  }

  Company* temp = largestParent(companies[i]);
  temp->merge1->parent = nullptr;
  temp->merge2->parent = nullptr;
  delete temp;
  
}

bool CompanyTracker::inSameCompany (int i, int j)
  /* Returns whether students i and j are currently in the same company.
     Returns true if i==j.
     Returns false if i or j (or both) is out of range. */
{
  Company* temp1 = largestParent(companies[i]);
  Company* temp2 = largestParent(companies[j]);
  if(temp1 == temp2){
    return true;
  }
  else {
    return false;
  }
}

Company* CompanyTracker::largestParent(Company*& c){
  if(c->parent == nullptr){
    return c;
  }
  else {
    largestParent(c->parent);
  }
}

