/******************************************************************************
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-15 Nicola Bonelli <nicola@pfq.io>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 ******************************************************************************/

#pragma once

#include <map>
#include <cat/functor/functor.hpp>

namespace cat
{
    // map is a functor:
    //

    template <> struct is_functor<std::map> : std::true_type { };

    // map instance:
    //

    namespace functor_map
    {
        template <typename Key, typename Fun, typename Functor>
        static auto fmap(Fun f, Functor && xs)
        {
            std::map<Key, decltype(f( forward_as<Functor>(xs.begin()->second) )) > out;

            for(auto & x : xs)
                out.insert(std::make_pair(x.first, f(forward_as<Functor>(x.second))));

            return out;
        }
    };


    template <typename Fun, typename K, typename A>
    struct FunctorInstance<std::map<K,A> const &, Fun> final : Functor<std::map<K,A> const &>::
    template __<Fun>
    {
        using B = typename std::result_of<Fun(A)>::type;

        std::map<K, B>
        fmap(Fun f, std::map<K, A> const &xs) override
        {
            return functor_map::fmap<K>(std::move(f), xs);
        }
    };

    template <typename Fun, typename K, typename A>
    struct FunctorInstance<std::map<K,A> &&, Fun> final : Functor<std::map<K,A> &&>::
    template __<Fun>
    {
        using B = typename std::result_of<Fun(A)>::type;

        std::map<K, B>
        fmap(Fun f, std::map<K, A> &&xs) override
        {
            return functor_map::fmap<K>(std::move(f), std::move(xs));
        }
    };


    // multimap is a functor:
    //

    template <> struct is_functor<std::multimap> : std::true_type { };

    // multimap instance:
    //

    namespace functor_multimap
    {
        template <typename Key, typename Fun, typename Functor>
        static auto fmap(Fun f, Functor && xs)
        {
            std::multimap<Key, decltype(f( forward_as<Functor>(xs.begin()->second) )) > out;

            for(auto & x : xs)
                out.insert(std::make_pair(x.first, f(forward_as<Functor>(x.second))));

            return out;
        }
    };


    template <typename Fun, typename K, typename A>
    struct FunctorInstance<std::multimap<K,A> const &, Fun> final : Functor<std::multimap<K,A> const &>::
    template __<Fun>
    {
        using B = typename std::result_of<Fun(A)>::type;

        std::multimap<K, B>
        fmap(Fun f, std::multimap<K, A> const &xs) override
        {
            return functor_multimap::fmap<K>(std::move(f), xs);
        }
    };

    template <typename Fun, typename K, typename A>
    struct FunctorInstance<std::multimap<K,A> &&, Fun> final : Functor<std::multimap<K,A> &&>::
    template __<Fun>
    {
        using B = typename std::result_of<Fun(A)>::type;

        std::multimap<K, B>
        fmap(Fun f, std::multimap<K, A> &&xs) override
        {
            return functor_multimap::fmap<K>(std::move(f), std::move(xs));
        }
    };
} // namespace cat

