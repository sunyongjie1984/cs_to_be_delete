// ServiceControlInterop.h

#pragma once

namespace ServiceControlInterop {

	public ref class ServiceControl abstract sealed
	{
	public:
		static void AddService(System::String^ serviceName, System::String^ displayName, System::String^ path);
		static void RemoveService(System::String^ serviceName);
		static void ActivateService(System::String^ serviceName);
		static void DeactivateService(System::String^ serviceName);

		static void RemoveAllPrivilegesFromService(System::String^ serviceName);

		static void SetServiceDelayedAutoStart(System::String^ serviceName);

		static bool IsServiceTriggerStart(System::String^ serviceName);
		static void SetServiceTriggerStartOnUSBArrival(System::String^ serviceName);
		static void SetServiceTriggerStartOnIPAddressArrival(System::String^ serviceName);
	};
}
