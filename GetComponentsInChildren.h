void GetComponentsInChildren(std::uintptr_t game_object, std::vector<std::uintptr_t>& renderers, int depth = 0)
{
    const auto component_list = driver.read<std::uint64_t>(game_object + 0x30);
    if (!component_list)
        return;

    const auto component_size = driver.read<int>(game_object + 0x40);
    if (!component_size)
        return;

    for (int idx{ 0 }; idx < component_size; ++idx)
    {
        const auto component = driver.read<std::uint64_t>(component_list + (0x10 * idx + 0x8));
        if (!component)
            continue;

        const auto component_ptr = driver.read<std::uint64_t>(component + 0x28);
        if (!component_ptr)
            continue;

        const auto component_name_ptr = driver.read<std::uint64_t>(component_ptr + 0x0);
        if (!component_name_ptr)
            continue;

        const auto component_name = driver.read<std::uint64_t>(component_name_ptr + 0x10);
        if (!component_name)
            continue;

        auto name = driver.read_string(component_name);

        if (name == e("SkinnedMeshRenderer") || name == e("MeshRenderer"))
            renderers.push_back(component);

        if (name == e("Transform"))
        {
            const auto child_list = driver.read<std::uint64_t>(component + 0x70);
            if (!child_list)
                continue;

            const auto child_size = driver.read<int>(component + 0x80);
            if (!child_size)
                continue;

            for (int i{ 0 }; i < child_size; ++i)
            {
                const auto child_transform = driver.read<std::uint64_t>(child_list + (0x8 * i));
                if (!child_transform)
                    continue;

                const auto child_game_object = driver.read<std::uint64_t>(child_transform + 0x30);
                if (!child_game_object)
                    continue;

                const auto child_object_name = driver.read<std::uint64_t>(child_game_object + 0x60);
                if (!child_object_name)
                    continue;

                const auto child_name = driver.read_string(child_object_name);

                GetComponentsInChildren(child_game_object, renderers, depth + 1);
            }
        }
    }
}
