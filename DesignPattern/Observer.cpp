#include "stdafx.h"
#include "Observer.h"
#include <algorithm>


using namespace std;
using namespace XFU;


void Subject::Attach(Observer* observer)
{
   if (find(_observers.begin(),_observers.end(),observer) == _observers.end())
   {
      _observers.push_back(observer);
   }
}

void Subject::Detach(Observer* observer)
{
   _observers.remove(observer);
}

void Subject::DetachAll()
{
   _observers.clear();
}

void Subject::Notify(const ObserverEvent& event)
{
   for (list<Observer*>::iterator it=_observers.begin(); it!=_observers.end(); it++)
   {
      (*it)->Update(event);
   }
}