//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "async.h"

using boost::asio::ip::tcp;

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket, std::size_t bulk_size_, void* handle)
    : socket_(std::move(socket)),sz(std::move(bulk_size_)),handle(handle)
  {
  }

  ~session(){
    async::disconnect(handle);
  }

  void start()
  {
    do_read();
  }

private:
  void do_read()
  {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            if(ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset){
              async::disconnect(handle);
            }

             ss= ss + data_[0];
             if(data_[0]=='\n'){
                async::receive(handle,ss.c_str(),ss.size());
                ss.clear();
             }
            do_read();
            int x=0;
            x=123;          
          }
        });
  }

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[1];
  void* handle;
  std::string ss;
  std::size_t sz;
};

class server
{
public:
  server(boost::asio::io_context& io_context, short port, std::size_t bulk_sz)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),bulk_size_(bulk_sz)
  {
    handle = async::connect(bulk_size_);
    do_accept();
  }

  ~server(){
    async::disconnect(handle);
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            if(async::get_status(handle)==1){
                async::disconnect(handle);
                handle = async::connect(bulk_size_);
            }
            std::make_shared<session>(std::move(socket),bulk_size_,handle)->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
  std::size_t bulk_size_;
  bool flag = false;
  void* handle;
};

