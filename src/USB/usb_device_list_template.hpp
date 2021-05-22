/*
This software is subject to the license described in the License.txt file
included with this software distribution. You may not use this file except
in compliance with this license.

Copyright (c) Dynastream Innovations Inc. 2016
All rights reserved.
*/
#include "types.h"

#include <vector>
#include <functional>


#define USBTemplateDeviceList    USBDeviceList<USBDeviceType>

/*
template <typename USBDeviceType>
template<typename Container_>
USBTemplateDeviceList::USBDeviceList(const Container_& tContainer_)
{
   Add(tContainer_.begin(), tContainer_.end());
   return;
}
*/

template <typename USBDeviceType>
USBTemplateDeviceList::~USBDeviceList()
{
   Clear();
   return;
}


template <typename USBDeviceType>
template <typename InputIterator>
USBTemplateDeviceList::USBDeviceList(InputIterator tFirst_, InputIterator tLast_)
{
   Add(tFirst_, tLast_);
   return;
}

template <typename USBDeviceType>
USBTemplateDeviceList::USBDeviceList(const USBTemplateDeviceList& clDeviceList_)
{
   Add(clDeviceList_);
   return;
}

template <typename USBDeviceType>
template<typename USBDeviceType_>
USBTemplateDeviceList::USBDeviceList(const USBDeviceList<USBDeviceType_>& clDeviceList_)
{
   Add(clDeviceList_);
   return;
}



template <typename USBDeviceType>
USBTemplateDeviceList& USBTemplateDeviceList::operator=(const USBTemplateDeviceList& clDeviceList_)
{
   if(this == &clDeviceList_)
      return *this;

   Clear();
   Add(clDeviceList_);
   return *this;
}


template <typename USBDeviceType>
template<typename USBDeviceType_>
USBTemplateDeviceList& USBTemplateDeviceList::operator=(const USBDeviceList<USBDeviceType_>& clDeviceList_)
{
   if(this == &clDeviceList_)
      return *this;

   Clear();
   Add(clDeviceList_);
   return *this;
}



template <typename USBDeviceType>
template <typename InputIterator>
void USBTemplateDeviceList::Add(InputIterator tFirst_, InputIterator tLast_)
{
   for(InputIterator i=tFirst_; i != tLast_; i++)
      Add(*i);

   //insert(clDeviceList.end(), tFirst_, tLast_);
   return;
}


template <typename USBDeviceType>
template <typename USBDeviceType_>
void USBTemplateDeviceList::Add(const USBDeviceList<USBDeviceType_>& clDeviceList_)
{
   ULONG ulSize = clDeviceList_.GetSize();
   for(ULONG i=0; i<ulSize; i++)
      Add(clDeviceList_[i]);  //!!keep track of iterator ourselves?

   //insert(clDeviceList.end(), clDeviceList_.clDeviceList.begin(), clDeviceList_.clDeviceList.end());    //!!do we have to make an iterator?
   return;
}


template <typename USBDeviceType>
void USBTemplateDeviceList::Add(const USBDeviceType& tDevice_)  //!!Return the address of the element?  Then we don't need GetAddress().
{
   //Container::const_iterator clIterator;
   //advance(clIterator, ulSize);

   clDeviceList.insert(clDeviceList.end(), new USBDeviceType(tDevice_));
   //clDeviceList.push_back(tDevice_);  //!! container universal?
   return;
}

template <typename USBDeviceType>
void USBTemplateDeviceList::Clear()
{
   std::size_t uiSize = clDeviceList.size();
   for(std::size_t i=0; i<uiSize; i++)
      delete clDeviceList[i];

   clDeviceList.clear();

   return;
}



template <typename USBDeviceType>
USBTemplateDeviceList USBTemplateDeviceList::GetSubList(typename USBDeviceList::CompareFunc pfCompareFunc_) const  //!!Copy!
{
   USBTemplateDeviceList clSubList;

   if(pfCompareFunc_ == NULL)
      return clSubList;

   typename Container::const_iterator clIterator;
   for(clIterator = clDeviceList.begin(); clIterator != clDeviceList.end(); clIterator++)
   {
      USBDeviceType const& tDevice = **clIterator;
      if(pfCompareFunc_(tDevice) == TRUE)
         clSubList.Add(tDevice);
   }

   return clSubList;
}



template <typename USBDeviceType>
const USBDeviceType& USBTemplateDeviceList::operator[](ULONG ulNum_) const
{
   if(ulNum_ >= clDeviceList.size())
      throw 0; //!!

   typename Container::const_iterator clIterator;
   clIterator = clDeviceList.begin();
   std::advance(clIterator, ulNum_);
   return **clIterator;
}


template <typename USBDeviceType>
const USBDeviceType* USBTemplateDeviceList::GetAddress(ULONG ulNum_) const
{
   if(ulNum_ >= clDeviceList.size())
      throw 0; //!!

   typename Container::const_iterator clIterator;
   clIterator = clDeviceList.begin();
   std::advance(clIterator, ulNum_);
   return *clIterator;
}
