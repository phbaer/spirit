/*=============================================================================
    Copyright (c) 2001-2014 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2014 Thomas Bernard

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(SPIRIT_NO_SKIP_JAN_16_2010_0802PM)
#define SPIRIT_NO_SKIP_JAN_16_2010_0802PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/x3/support/context.hpp>
#include <boost/spirit/home/x3/support/unused.hpp>
#include <boost/spirit/home/x3/core/parser.hpp>

namespace boost { namespace spirit { namespace x3
{
    struct no_case_tag;

    // propagate no_case information through the context
    template <typename Subject>
    struct no_case_directive : unary_parser<Subject, no_case_directive<Subject>>
    {
        typedef unary_parser<Subject, no_case_directive<Subject> > base_type;
        static bool const is_pass_through_unary = true;
        static bool const handles_container = Subject::handles_container;

        no_case_directive(Subject const& subject)
          : base_type(subject) {}

        template <typename Iterator, typename Context
          , typename RContext, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context const& context, RContext& rcontext, Attribute& attr) const
        {
            return this->subject.parse(
                first, last
              , make_context<no_case_tag>(unused(), context)
              , rcontext
              , attr);
        }
    };

    struct no_case_gen
    {
        template <typename Subject>
        no_case_directive<typename extension::as_parser<Subject>::value_type>
        operator[](Subject const& subject) const
        {
            return {as_parser(subject)};
        }
    };

    no_case_gen const no_case = no_case_gen();
}}}

#endif
