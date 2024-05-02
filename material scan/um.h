#include <memory>
#include <Windows.h>
#include <string>
#include <Psapi.h>
#include <TlHelp32.h>
namespace cant_remove_due_to_strict_nda::crazy_material_dumper {
	typedef struct crazy_module {uint64_t crazy_base;uint64_t crazy_size;}crazymodule_t;
	inline HANDLE crazy_process_handle = 0;
	bool crazy_meth_setup( );
	void crazy_read( uintptr_t, void*, size_t );
	template <typename type>
	inline type crazy_read( uintptr_t address ) {type crazy_buffer{};crazy_read( address, &crazy_buffer, sizeof( type ) );return crazy_buffer;}
	void crazy_write( uintptr_t, void*, size_t );
	template <typename type>
	inline void crazy_write( uintptr_t address, type buffer ) {crazy_write( address, &buffer, sizeof( buffer ) );}
	crazymodule_t crazy_get_module( const std::wstring& name );
}