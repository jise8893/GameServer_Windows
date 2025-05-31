#pragma once
class IocpEvent; // 전방 선언

class IocpObject : std::enable_shared_from_this<IocpObject>
{
public:
	IocpObject() = default;
	virtual ~IocpObject() = default;
public:
	virtual HANDLE GetHandle() = 0;
	virtual void Dispatch(IocpEvent* iocpEvent, DWORD numOfBytes) = 0;
};

/// 
/// @class IocpCore
/// Iocp 객체를 관리하고 이벤트를 등록하는 클래스이다.
/// IocpObject를 상속받는 객체를 등록하고 대기 스레드 큐로 진입한다. IOCompletion Queue에서 반환되는 경우 
/// TID는 Windows Release IOCP Thread Queue로 이동한다.
/// 
class IocpCore
{
public:
	IocpCore();
	~IocpCore();
public:
	HANDLE GetHandle() { return m_hIocp; }
	bool Dispatch();
	bool Register(std::shared_ptr<IocpObject> pIocpObject);

private:
	HANDLE m_hIocp;
};

