struct dynamic_array {
uint64_t base;
uint64_t mem_id;
uint64_t sz;
uint64_t cap;
};

if (config.Includes.esp.chams.select == 0) 
                        continue;

                    const auto player_model = entity->playerModel();
                    if (!player_model)
                        continue;

                    const auto multi_mesh = player_model->_multiMesh();
                    if (!multi_mesh)
                        continue;

                    const auto renderers = multi_mesh->Renderersk__BackingField();

                    if (!renderers)
                        continue;

                    for (std::uint32_t idx{ 0 }; idx < renderers->size(); idx++)
                    {
                        const auto renderer = renderers->get(idx);
                        if (!renderer)
                            continue;

                        const auto untity_object = driver.read<std::uintptr_t>(renderer + 0x10);
                        if (!untity_object)
                            continue;

                        const auto material_list = driver.read<systems::dynamic_array>(untity_object + 0x148);

                        if (material_list.sz < 1 || material_list.sz > 5)
                            continue;

                        for (std::uint32_t idx{ 0 }; idx < material_list.sz; idx++)
                            driver.write<unsigned int>(material_list.base + (idx * 0x4), chams);
                    }
