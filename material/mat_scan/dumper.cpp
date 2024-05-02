#include "usermode.h"
#include "json.hpp"
#include <fstream>

using nlohmann::json;

int main( ) {
	p9::memory::setup( );
	auto game_assembly = p9::memory::get_module( L"GameAssembly.dll" );
	std::ifstream input( "json.txt" );
	json swag;
	input >> swag;
	input.close( );
	auto sneed = swag[ "CheatTable" ][ "CheatEntries" ][ "CheatEntry" ];
	std::ofstream output( "material_output.txt" );
	for ( auto& entry : sneed ) {
		std::string addr_s = entry[ "Address" ];
		unsigned long long value;
		std::istringstream iss( addr_s );
		iss >> std::hex >> value;
		value -= 0x88;
		char _name[ 255 ];
		auto _addy = p9::memory::read<uintptr_t>( value + 0x30 );
		p9::memory::read( _addy, _name, 255 );
		_name[ 254 ] = 0;
		std::string name( _name );
		auto key = p9::memory::read<uint32_t>( value + 0x8 );
		output << "material name" << name << "material address" << key << "\n";
	}
	output.close( );
}