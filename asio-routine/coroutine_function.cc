/**
 * Copyright (c) 2012, PICHOT Fabien Paul Leonard <pichot.fabien@gmail.com>
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
**/

#include "asio-routine/coroutine_function.hh"

namespace tnet {
  
coroutine_function::coroutine_function(asio::io_service& io)
  : coroutine_object{io, ""}
{
}

coroutine_function::coroutine_function(coroutine_object &parent,
                                       std::string const& name)
  : coroutine_object{parent, name}
{
}

void
coroutine_function::yield()
{
  (*this->_ca)();
  if (bool(_coro) == false)
    throw std::runtime_error{"stop"};
}

void
coroutine_function::cont()
{
  (*this->_coro)();
}

void
coroutine_function::show_children(int indent)
{
  printfmt("%[%] %%\n",
           std::string{" "} * indent,
           this,
           this->name(),
           (this->_children.empty() ? " " : ":"));
  indent += 4;
  for (auto const&f: this->_children)
  {
    if (auto ptr = dynamic_cast<coroutine_function*>(f))
      ptr->show_children(indent);
    else
      printfmt("%[%] %\n", std::string{" "} * indent, &f, f->name());
  }
}

} /* tnet */
