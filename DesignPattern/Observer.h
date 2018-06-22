#pragma once


#include <string>
#include <list>
#include "basedef.h"


namespace XFU
{
   class _DP_SPEC ObserverEvent : public Object
   {
   public:
      explicit ObserverEvent(const std::wstring& id)
         :_id(id)
      {}

      virtual ~ObserverEvent()
      {}

      const std::wstring& Getid() const
      {
         return _id;
      }

   private:
      std::wstring _id;
   };



   class _DP_SPEC Observer : virtual public Interface
   {
   public:
      Observer()
      {}

      virtual ~Observer()
      {}

      virtual void Update(const ObserverEvent& event) = 0;
   };


   class _DP_SPEC Subject : private NonCopyable
   {
   public:
      Subject()
      {}

      virtual ~Subject()
      {
         _observers.clear();
      }

      void Attach(Observer* observer);
      void Detach(Observer* observer);
      void DetachAll();

   protected:
      void Notify(const ObserverEvent& event);

   private:
      std::list<Observer*> _observers;
   };
}
