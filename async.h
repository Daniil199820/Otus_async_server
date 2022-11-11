#pragma once

#include <cstddef>
#include "Context.h"

namespace async {

using handle_t = void *;

handle_t connect(std::size_t bulk,std::ostream& os_out=std::cout);
void receive(handle_t handle, const char *data, std::size_t size);
void disconnect(handle_t handle);
int get_status(handle_t handle);

}