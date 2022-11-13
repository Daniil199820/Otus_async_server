#include <iostream>

#include "Async_server.h"

/*int main(int, char *[]) {
    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    auto h2 = async::connect(bulk);
    async::receive(h, "1", 1);
    async::receive(h2, "1\n", 2);
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);
    async::disconnect(h);
    async::disconnect(h2);

    return 0;
}
*/
int main(int argc, char* argv[])
{
  try
  {
    //if (argc != 3)
   // {
   //   std::cerr << "Usage: <port> <bulk size>\n";
   //   return 1;
   // }

    boost::asio::io_context io_context;

    //server server(io_context, std::atoi(argv[1]),std::atoi(argv[2]));

      server server(io_context, 9000,3);

    io_context.run();
  }
  catch (const std::exception& ex)
  {
    std::cerr << "Exception: " << ex.what() << "\n";
  }

  return 0;
}