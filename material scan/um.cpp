#include <Windows.h>
#include <winternl.h>
#include <Psapi.h>
#include "um.h"
bool cant_remove_due_to_strict_nda::crazy_material_dumper::crazy_meth_setup( ) {HANDLE ss = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );if ( ss ) {HANDLE process = NULL;PROCESSENTRY32 pe;pe.dwSize = sizeof( PROCESSENTRY32 );if ( Process32First( ss, &pe ) ) {do {if ( !wcscmp( pe.szExeFile, ( L"RustClient.exe" ) ) ) {process = OpenProcess( PROCESS_ALL_ACCESS, false, pe.th32ProcessID );}} while ( Process32Next( ss, &pe ) );}CloseHandle( ss );crazy_process_handle = process;}return crazy_process_handle;}
void cant_remove_due_to_strict_nda::crazy_material_dumper::crazy_read( uintptr_t address, void* buffer, size_t size ) {if (crazy_process_handle )ReadProcessMemory(crazy_process_handle, ( LPCVOID )address, buffer, size, 0 );}
void cant_remove_due_to_strict_nda::crazy_material_dumper::crazy_write( uintptr_t address, void* buffer, size_t size ) {if (crazy_process_handle )WriteProcessMemory(crazy_process_handle, ( LPVOID )address, &buffer, size, NULL );}
cant_remove_due_to_strict_nda::crazy_material_dumper::crazymodule_t cant_remove_due_to_strict_nda::crazy_material_dumper::crazy_get_module( const std::wstring& name ) {crazymodule_t mod = { 0 };HANDLE ss = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, GetProcessId(crazy_process_handle ) );if ( ss ) {MODULEENTRY32 me;me.dwSize = sizeof( MODULEENTRY32 );if ( Module32First( ss, &me ) ) {do {if ( !wcscmp( me.szModule, name.data( ) ) ) {mod.crazy_base = ( uint64_t )me.modBaseAddr;mod.crazy_size = ( uint64_t )me.modBaseSize;break;}} while ( Module32Next( ss, &me ) );}CloseHandle( ss );}return mod;}