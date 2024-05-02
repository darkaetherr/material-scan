#include "um.h"
#include "json.h"
#include <fstream>

using nlohmann::json;

int main( ) {
    // Setup
    cant_remove_due_to_strict_nda::crazy_material_dumper::crazy_meth_setup();

    // Get module
    auto game_assembly = cant_remove_due_to_strict_nda::crazy_material_dumper::crazy_get_module(L"GameAssembly.dll");

    // Read JSON input
    std::ifstream input("json.txt");
    nlohmann::json crazy_swag;
    input >> crazy_swag;
    input.close();

    // Open output file
    std::ofstream output("material_output.txt");

    // Process each entry in the JSON
    auto crazy_sneed = crazy_swag["CheatTable"]["CheatEntries"]["CheatEntry"];
    for (auto& entry : crazy_sneed) {
        // Extract address
        std::string addr_s = entry["Address"];
        unsigned long long crazy_value;
        std::istringstream iss(addr_s);
        iss >> std::hex >> crazy_value;
        crazy_value -= 0x88;

        // Read name
        char material_name[255];
        auto material_addy = cant_remove_due_to_strict_nda::crazy_material_dumper::crazy_read<uintptr_t>(crazy_value + 0x30);
        cant_remove_due_to_strict_nda::crazy_material_dumper::crazy_read(material_addy, material_name, 255);
        material_name[254] = 0;
        std::string name(material_name);

        // Read key
        auto material_address = cant_remove_due_to_strict_nda::crazy_material_dumper::crazy_read<uint32_t>(crazy_value + 0x8);

        // Write to output file
        output << "material name: " << name << ", material address: " << material_address << "\n";
    }

    // Close output file
    output.close();

    return 0;
}