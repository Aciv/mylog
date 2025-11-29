# A simple Log
## Characteristics
1. Use Singleton Pattern, only one Log Intance exist in process.
2. Support Synchronous and Asynchronous.
3. Support Log in file and stdout.
4. Support sample pattern.
## Usage
### Get Instance and Init

```cpp
Aciv::utility::Log& logger = Aciv::utility::Log::get_Instance();
logger.init(1024, 512);
```
Init function have two parameter ``_max_queue_size`` and ``_meessage_limit``, and should be used only once.

Denote the blockqueue size used for Asynchronous write and log message limit respectively. So if blockqueue equals to zero, log will be Synchronous, and other for Asynchronous.

### Set Sender
Sender is used to write log message to stream. This log support two sender are File Sender and Stdout Sender respectively.
```cpp
logger.add_sender(std::make_unique<Aciv::utility::Stdout_sender>());
logger.add_sender(std::make_unique<Aciv::utility::File_sender>("your log file name"));
```
### Set Pattern
This simple pattern supports prompt as follow
```
%l -> level
%v -> message
%y -> year
%m -> month
%d -> day
%w -> weekday
%T -> year/month/day hours:minte:second
%t -> hours:minte:second
```
When get a unknow prompt, simply ignore it, and move out the log message.
Set pattern as follow:
```cpp
logger.set_pattern("[%l] [%T]: %v\n");
```
### Log message
Log message as follow:
```cpp
logger.record(log_level, "Your log message");
```
Supported level defined in sender/level.h
```cpp
namespace Aciv::utility{
	enum class level : std::uint8_t
	{
		none		=	(1 << 0),
		info		=	(1 << 1),
		warning		=	(1 << 2),
		error		=	(1 << 3),
		critical	=	(1 << 4),
		debug		=	(1 << 5),
		all			=	(1 << 6)
	};
```