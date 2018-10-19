#ifndef __CLOSURE_HPP_
#define __CLOSURE_HPP_

#include <cstddef>

namespace Interpreter {
namespace TAC {

struct Closure {

private:
  std::size_t *m_continuation;
};

}
}

#endif
