#ifndef LP_MP_TEMPLATE_UTILITIES
#define LP_MP_TEMPLATE_UTILITIES

#include <type_traits>
#include <utility>
#include <tuple>
#include "config.hxx"
#include <cstddef>
#include <utility>
#include "meta/meta.hpp"

// mostly obsolete due to the meta-library
// do zrobienia: remove altogether

namespace LP_MP {

   // tuple iteration
   template <typename Tuple, typename F, std::size_t ...Indices>
      void for_each_tuple_impl(Tuple&& tuple, F&& f, std::index_sequence<Indices...>) {
         using swallow = int[];
         (void)swallow{1,
            (f(std::get<Indices>(std::forward<Tuple>(tuple))), void(), int{})...
         };
      }

   template <typename Tuple, typename F>
      void for_each_tuple(Tuple&& tuple, F&& f) {
         constexpr std::size_t N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
         for_each_tuple_impl(std::forward<Tuple>(tuple), std::forward<F>(f),
               std::make_index_sequence<N>{});
      }

   template<class LIST> using tuple_from_list = meta::apply<meta::quote<std::tuple>, LIST>;


   // iterate over two tuples in order
   template <typename Tuple, typename F, std::size_t ...Indices>
      void for_each_tuple_pair_impl(Tuple&& tuple_1, Tuple&& tuple_2, F&& f, std::index_sequence<Indices...>) {
         using swallow = int[];
         (void)swallow{1,
            (f(std::get<Indices>(std::forward<Tuple>(tuple_1)), std::get<Indices>(std::forward<Tuple>(tuple_2))), void(), int{})...
         };
      }

   template <typename Tuple, typename F>
      void for_each_tuple_pair(Tuple&& tuple_1, Tuple&& tuple_2, F&& f) {
         constexpr std::size_t N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
         for_each_tuple_pair_impl(std::forward<Tuple>(tuple_1), std::forward<Tuple>(tuple_2), std::forward<F>(f),
               std::make_index_sequence<N>{});
      }
}

#endif // LP_MP_TEMPLATE_UTILITIES
