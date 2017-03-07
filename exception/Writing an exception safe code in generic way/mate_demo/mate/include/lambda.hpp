/*! @file lambda.hpp
 *  @brief Creating an anonymous function object (pure function).
 *
 *  @author   JaeWook Choi (zzzz.ooo "at' gmail.com)
 *  @version  1.01
 *  @date 12.12.2006
 *  @warning  This software is provided "as is" without express or implied warranty.
 *  @warning  Use it at your own risk!
 */
#if !defined(__LAMBDA_HPP__INCLUDED__)
#define __LAMBDA_HPP__INCLUDED__

/*! @page lambda_operations Creating an anonymous function object (pure function).
 *
 *  @anchor lambda_contents
 *
 *    -# @ref lambda_introduction
 *    -# @ref lambda_basic_usage
 *    -# @ref lambda_advanced_usage
 *    -# @ref lambda_references
 *
 *  @section lambda_introduction Introduction.
 *
 *  continued...
 *
 *  @ref lambda_contents "[top]"
 *
 *  @section lambda_basic_usage Basic Usage.
 *
 *  continued...
 *
 *  @ref lambda_contents "[top]"
 *
 *  @section lambda_advanced_usage Advanced Usage.
 *
 *  continued...
 *
 *  @ref lambda_contents "[top]"
 *
 *  @section lambda_references References.
 *
 *    -# <a href="http://www.kmonos.net/alang/klx/test/petitfex.hpp">Anonymous function object creation.</a>
 *
 *  @ref lambda_contents "[top]"
 */

// --------------------------------------------------------------------------------
// Compiler configuration.
// --------------------------------------------------------------------------------

#if defined(_MSC_VER)
// --------------------------------------------------------------------------------
// MSVC common.
// --------------------------------------------------------------------------------

#ifndef AM_STDCALL
#define AM_STDCALL __stdcall
#endif

#define AM_STDCALL_FN_POINTER0(RET, FN) \
  RET (AM_STDCALL * FN)()

#define AM_STDCALL_FN_POINTER1(RET, FN, A1) \
  RET (AM_STDCALL * FN)(A1)

#define AM_STDCALL_FN_POINTER2(RET, FN, A1, A2) \
  RET (AM_STDCALL * FN)(A1, A2)

#define AM_STDCALL_FN_POINTER3(RET, FN, A1, A2, A3) \
  RET (AM_STDCALL * FN)(A1, A2, A3)


#if 1200 >= _MSC_VER
// --------------------------------------------------------------------------------
// VC6 or earlier.
// --------------------------------------------------------------------------------

// Can not partial template specialization.
#define AM_NO_PARTIAL_TEMPLATE_SPECIALIZATION

// VC6 can not return void.
#define AM_CAN_NOT_RETURN_VOID

#else
// --------------------------------------------------------------------------------
// VC7 or higher.
// --------------------------------------------------------------------------------

#endif
#else
// --------------------------------------------------------------------------------
// Non-VC
// --------------------------------------------------------------------------------

#if defined(__GNUC__)
// --------------------------------------------------------------------------------
// GCC
// --------------------------------------------------------------------------------

#ifndef AM_STDCALL
#define AM_STDCALL __attribute__((stdcall))
#endif

#define AM_STDCALL_FN_POINTER0(RET, FN) \
  RET (* FN)() AM_STDCALL

#define AM_STDCALL_FN_POINTER1(RET, FN, A1) \
  RET (* FN)(A1) AM_STDCALL

#define AM_STDCALL_FN_POINTER2(RET, FN, A1, A2) \
  RET (* FN)(A1, A2) AM_STDCALL

#define AM_STDCALL_FN_POINTER3(RET, FN, A1, A2, A3) \
  RET (* FN)(A1, A2, A3) AM_STDCALL

#else   // #if defined(__GNUC__)

// --------------------------------------------------------------------------------
// Misc.
// --------------------------------------------------------------------------------

#ifndef AM_STDCALL
#define AM_STDCALL
#endif

#undef AM_BIND_ENABLE_STDCALL

#endif    // #if defined(__GNUC__)

#endif

// --------------------------------------------------------------------------------
// End of compiler configuration.
// --------------------------------------------------------------------------------


// #define AM_BIND_ENABLE_STDCALL

namespace am
{

//! namespace of lambda.
/*! Defines simple set of boolean lambda operations and member data pointer access.
 *
 *  It only supports a set of boolean lambda operations as listed below:
 *    -# unary boolean operator : !
 *    -# binary boolean operator : ==, !=, <, >, <=, >=, &&, ||
 *
 *  and member data pointer access: (*** Read only access ! ***)
 *    -# unary operator : var_type1::operator &()
 *    -# binary operator : ->*
 *
 *  Supports 3 lambda place holder: am::lambda::_1, am::lambda::_2, am::lambda::_3
 *
 *  Binding free function or member function up to 3 arguments supports to
 *  collaborate with the lambda place holder.
 *
 */
namespace lambda
{

// --------------------------------------------------------------------------------

namespace detail
{

// --------------------------------------------------------------------------------

/*!
 *  @internal Tag of lambda operator.
 *  All lambda pure functions are derived from lambda_op_tag.
 */
struct lambda_op_tag { };

} // namespace detail

// --------------------------------------------------------------------------------

/*!
 *  @internal 1st lambda place holder type.
 */
struct var_type1
{
  // --------------------------------------------------------------------------------

  /*!
   *  @internal address_of pure function.
   *  Return the address of the variable type 1.
   *
   *  @sa operator &()
   */
  struct address_of : public detail::lambda_op_tag
  {
    var_type1 const & v1_;
    address_of(var_type1 const & v1) : v1_( v1 ) { }

    template<class T1, class T2, class T3> T1 * operator ()(T1 & t1, T2 & t2, T3 & t3) const { return & v1_( t1, t2, t3 ); }
    template<class T1, class T2> T1 * operator ()(T1 & t1, T2 & t2) const { return & v1_( t1, t2 ); }
    template<class T1> T1 * operator ()(T1 & t1) const { return & v1_( t1 ); }

  };  // struct address_of : public detail::lambda_op_tag

  // --------------------------------------------------------------------------------

  address_of operator &() const
  {
    return address_of( *this );
  }

  // --------------------------------------------------------------------------------

  template<class T1, class T2, class T3> T1 & operator ()(T1 & t1, T2, T3) const { return t1; }
  template<class T1, class T2> T1 & operator ()(T1 & t1, T2) const { return t1; }
  template<class T1> T1 & operator ()(T1 & t1) const { return t1; }

private:
  // It is required to supply one or more input arguments.
  void operator ()() const;

};  // struct var_type1

// --------------------------------------------------------------------------------

/*!
 *  @internal 2nd lambda place holder type.
 */
struct var_type2
{
  // --------------------------------------------------------------------------------

  /*!
   *  @internal address_of pure function.
   *  Return the address of the variable type 1.
   *
   *  @sa operator &()
   */
  struct address_of : public detail::lambda_op_tag
  {
    var_type2 const & v2_;
    address_of(var_type2 const & v2) : v2_( v2 ) { }

    template<class T1, class T2, class T3> T2 * operator ()(T1 & t1, T2 & t2, T3 & t3) const { return & v2_( t1, t2, t3 ); }
    template<class T1, class T2> T2 * operator ()(T1 & t1, T2 & t2) const { return & v2_( t1, t2 ); }

  };  // struct address_of : public detail::lambda_op_tag

  // --------------------------------------------------------------------------------

  address_of operator &() const
  {
    return address_of( *this );
  }

  template<class T1, class T2, class T3> T2 & operator ()(T1, T2 & t2, T3) const { return t2; }
  template<class T1, class T2> T2 & operator ()(T1, T2 & t2) const { return t2; }

private:
  // It is required to supply two or more input arguments.
  template<class T1> T1 operator ()(T1) const;
  void operator ()() const;

};  // struct var_type2

// --------------------------------------------------------------------------------

/*!
 *  @internal 3rd lambda place holder type.
 */
struct var_type3
{
  // --------------------------------------------------------------------------------

  /*!
   *  @internal address_of pure function.
   *  Return the address of the variable type 1.
   *
   *  @sa operator &()
   */
  struct address_of : public detail::lambda_op_tag
  {
    var_type3 const & v3_;
    address_of(var_type3 const & v3) : v3_( v3 ) { }

    template<class T1, class T2, class T3> T3 * operator ()(T1 & t1, T2 & t2, T3 & t3) const { return & v3_( t1, t2, t3 ); }

  };  // struct address_of : public detail::lambda_op_tag

  // --------------------------------------------------------------------------------

  address_of operator &() const
  {
    return address_of( *this );
  }

  template<class T1, class T2, class T3> T3 & operator ()(T1, T2, T3 & t3) const { return t3; }

private:
  // It is required to supply three input arguments.
  template<class T1, class T2> T2 operator ()(T1, T2) const;
  template<class T1> T1 operator ()(T1) const;
  void operator ()() const;

};  // struct var_type3

// --------------------------------------------------------------------------------

static var_type1 _1; //!< 1st lambda place holder.
static var_type2 _2; //!< 2nd lambda place holder.
static var_type3 _3; //!< 3rd lambda place holder.

// --------------------------------------------------------------------------------

/*!
 *  @internal  Pure Function to support member data pointer access.
 *
 */
template<class P, class O, class U> struct pf_memdata : public detail::lambda_op_tag
{
  P opnd_;
  U (O::*pu_);
  pf_memdata(P opnd, U (O::*pu)) : opnd_( opnd ), pu_( pu ) { }
  template<class T1, class T2, class T3> U const & operator ()(T1 & t1, T2 & t2, T3 & t3) const { return opnd_( t1, t2, t3 )->*pu_; }
  template<class T1, class T2> U const & operator ()(T1 & t1, T2 & t2) const { return opnd_( t1, t2 )->*pu_; }
  template<class T1> U const & operator ()(T1 & t1) const { return opnd_( t1 )->*pu_; }

  // --------------------------------------------------------------------------------

  /*!
   *  @internal address_of pure function.
   *  Return the address of the member data accessed.
   *
   *  @sa operator &()
   */
  struct address_of : public detail::lambda_op_tag
  {
    pf_memdata<P, O, U> const & pmd_;
    address_of(pf_memdata<P, O, U> const & pmd) : pmd_( pmd ) { }

    template<class T1, class T2, class T3> U const * operator ()(T1 & t1, T2 & t2, T3 & t3) const { return & pmd_( t1, t2, t3 ); }
    template<class T1, class T2> U const * operator ()(T1 & t1, T2 & t2) const { return & pmd_( t1, t2 ); };
    template<class T1> U const * operator ()(T1 & t1) const { return & pmd_( t1 ); }

  };  // struct address_of : public detail::lambda_op_tag

  address_of operator &() const
  {
    return address_of( *this );
  }

};  // template<class P, class O, class U> struct pf_memdata : public detail::lambda_op_tag

/*! @internal ->* operator overloading.
 *  Helper fucntion for pf_memdata.
 *
 *  @code
 struct MyData
 {
   int id;
   std::string msg;
 };

 MyData InitMyData(int id, std::string msg)
 {
   MyData md; md.id = id; md.msg = msg;
   return md;
 }

 void main()
 {
   std::vector<MyData> myDataVec;

   myDataVec.push_back( InitMyData( 1, "hello" ) );
   myDataVec.push_back( InitMyData( 2, "world!" ) );

   std::vector<MyData>::iterator it_f = std::find_if( myDataVec.begin(), myDataVec.end(),
     &am::lambda::_1->*&MyData::id == 2 ); // Find the iterator of the element whose id is 2.
   assert( it_f != myDataVec.end() );

   std::cout << it_f->msg.c_str() << std::endl;  // Print out "world!"

   std::pair<float, MyData> myPair = std::make_pair( 1.2f, InitMyData( 3, "lambda!" ) );

   bool ret1 = ( &( &am::lambda::_1->*&std::pair<float, MyData>::second )->*&MyData::id == 3 )( myPair );
   assert( true == ret1 );

   bool ret2 = ( &( am::lambda::_1->*&std::pair<float, MyData>::second )->*&MyData::id == 3 )( &myPair );
   assert( true == ret2 );
 }
 *  @endcode
 */
template<class P, class O, class U> inline
pf_memdata<P, O, U> operator ->*(P opnd, U (O::*pu))
{
  return pf_memdata<P, O, U>( opnd, pu );
}

// --------------------------------------------------------------------------------

//! Predicate. 
/*! Convert a boolean expression into null-nary or unary predicate.
 */
struct condition : public detail::lambda_op_tag
{
  bool b_;
  condition(bool b) : b_( b) { }
  template<class T1, class T2, class T3> bool operator ()(T1, T2, T3) const { return b_; }
  template<class T1, class T2> bool operator ()(T1, T2) const { return b_; }
  template<class T1> bool operator ()(T1) const { return b_; }
  bool operator ()() const { return b_; }

};  // struct condition : public detail::lambda_op_tag

// --------------------------------------------------------------------------------

namespace detail
{

// --------------------------------------------------------------------------------

/*!
 *  @internal Determines whether or not the specified template type is a derived
 *  from lambda_op_tag.
 */
template<class T> struct is_lambda_op
{
  static T testee_;
  static char tester_(lambda_op_tag &);   // true condition.
    static int tester_(...);            // false condition.

  enum { value = ( sizeof( char ) == sizeof( tester_( testee_ ) ) ) };

};  // template<typename T> struct is_lambda_op

// --------------------------------------------------------------------------------

/*! @struct am::lambda::detail::if_
 *  @internal if meta template class.
 *  Select type according to the boolean condition.
 */

#if defined(AM_NO_PARTIAL_TEMPLATE_SPECIALIZATION)

template<bool cond, typename THEN, typename ELSE> struct if_
{
  template<bool> struct selector;
  template<> struct selector<true>  { typedef THEN type; };
  template<> struct selector<false> { typedef ELSE type; };

  typedef typename selector<cond>::type type;

};  // template <bool cond, typename THEN, typename ELSE> struct if_

#else // #if defined(AM_NO_PARTIAL_TEMPLATE_SPECIALIZATION)

template<bool, typename THEN, typename ELSE> struct if_;
template<typename THEN, typename ELSE> struct if_<true, THEN, ELSE>   { typedef THEN type; };
template<typename THEN, typename ELSE> struct if_<false, THEN, ELSE>  { typedef ELSE type; };

#endif  // #if defined(AM_NO_PARTIAL_TEMPLATE_SPECIALIZATION)

// --------------------------------------------------------------------------------

/*!
 *  @internal Lambda value.
 */
template<class V> struct lambda_val
{
  V v_;
  lambda_val(V v) : v_( v ) { }
  template<class T1, class T2, class T3> V operator ()(T1, T2, T3) const { return v_; }
  template<class T1, class T2> V operator ()(T1, T2) const { return v_; }
  template<class T1> V operator ()(T1) const { return v_; }
  V operator ()() const { return v_; }

};  // template<class V> struct lambda_val

// --------------------------------------------------------------------------------

/*!
 *  @internal Transform a value to a lambda value
 */
template<class V> struct tr
{
  typedef typename if_< is_lambda_op<V>::value, V, lambda_val<V> >::type type;

};  // template<typename V> struct tr

/*!
 *  @internal Template specialization for the 1st lambda place holder.
 */
template<> struct tr<var_type1> { typedef var_type1 type; };

/*!
 *  @internal Template specialization for the 2nd lambda place holder.
 */
template<> struct tr<var_type2> { typedef var_type2 type; };

/*!
 *  @internal Template specialization for the 3rd lambda place holder.
 */
template<> struct tr<var_type3> { typedef var_type3 type; };


// --------------------------------------------------------------------------------

} // namespace detail

// --------------------------------------------------------------------------------

/*! @def UNARY_BOOL_OP(NAME, OP)
 *  @internal Defines an unary boolean lambda operator functor, @a NAME and its
 *  helper operator overloading, @a OP.
 *
 *  @code UNARY_BOOL_OP( pf_not, ! ) @endcode
 *
 *  generates the equivalent code snippet as shown below,
 *
 *  @code
 template<class P> struct pf_not : public detail::lambda_op_tag
 {
   P opnd_;
   pf_not(P opnd) : opnd_( opnd ) { }
   template<class T1, class T2, class T3> bool operator ()(T1 t1, T2 t2, T3 t3) const { return ! opnd_( t1, t2, t3 ); }
   template<class T1, class T2> bool operator ()(T1 t1, T2 t2) const { return ! opnd_( t1, t2 ); }
   template<class T1> bool operator ()(T1 t1) const { return ! opnd_( t1 ); }
   bool operator ()() const { return ! opnd_(); }
 };
 template<class P> inline
 pf_not<typename detail::tr<P>::type>
 operator !(P opnd)
 {
   typedef typename detail::tr<P>::type opnd_type;
   return pf_not<opnd_type>( opnd_type( opnd ) );
 }
 *  @endcode
 */
#define UNARY_BOOL_OP(NAME, OP) \
template<class P> struct NAME : public detail::lambda_op_tag \
{ \
  P opnd_; \
  NAME(P opnd) : opnd_( opnd ) { } \
  template<class T1, class T2, class T3> bool operator ()(T1 t1, T2 t2, T3 t3) const { return OP opnd_( t1, t2, t3 ); } \
  template<class T1, class T2> bool operator ()(T1 t1, T2 t2) const { return OP opnd_( t1, t2 ); } \
  template<class T1> bool operator ()(T1 t1) const { return OP opnd_( t1 ); } \
  bool operator()() const { return OP opnd_(); } \
}; \
template<class P> inline \
NAME<typename detail::tr<P>::type> \
operator OP(P opnd) \
{ \
  typedef typename detail::tr<P>::type opnd_type; \
  return NAME<opnd_type>( opnd_type( opnd ) ); \
}

UNARY_BOOL_OP( pf_not,    !  )

#undef UNARY_BOOL_OP

// --------------------------------------------------------------------------------

/*! @def BINARY_BOOL_OP(NAME, OP)
 *  @internal Defines a binary boolean lambda operator functor, @a NAME and its
 *  helper operator overloading, @a OP.
 *
 *  @code BINARY_BOOL_OP( pf_eq, == ) @endcode
 *
 *  generates the equivalent code snippet as shown below,
 *
 *  @code
 template<class L, class R> struct pf_eq : public detail::lambda_op_tag
 {
   L lhs_; R rhs_;
   pf_eq(L lhs, R rhs) : lhs_( lhs ), rhs_( rhs ) { }
   template<class T1, class T2, class T3> bool operator ()(T1 t1, T2 t2, T3 t3) const { return lhs_( t1, t2, t3 ) == rhs_( t1, t2, t3 ); }
   template<class T1, class T2> bool operator ()(T1 t1, T2 t2) const { return lhs_( t1, t2 ) == rhs_( t1, t2 ); }
   template<class T1> bool operator ()(T1 t1) const { return lhs_( t1 ) == rhs_( t1 ); }
   bool operator ()() const { return lhs_() == rhs_(); }
 };
 template<class L, class R> inline
 pf_eq<typename detail::tr<L>::type, typename detail::tr<R>::type>
 operator ==(L lhs, R rhs)
 {
   typedef typename detail::tr<L>::type lhs_type;
   typedef typename detail::tr<R>::type rhs_type;
   return pf_eq<lhs_type, rhs_type>( lhs_type( lhs ), rhs_type( rhs ) );
 }
 *  @endcode
 */
#define BINARY_BOOL_OP(NAME, OP) \
template<class L, class R> struct NAME : public detail::lambda_op_tag \
{ \
  L lhs_; R rhs_; \
  NAME(L lhs, R rhs) : lhs_( lhs ), rhs_( rhs ) { } \
  template<class T1, class T2, class T3> bool operator ()(T1 t1, T2 t2, T3 t3) const { return lhs_( t1, t2, t3 ) OP rhs_( t1, t2, t3 ); } \
  template<class T1, class T2> bool operator ()(T1 t1, T2 t2) const { return lhs_( t1, t2 ) OP rhs_( t1, t2 ); } \
  template<class T1> bool operator ()(T1 t1) const { return lhs_( t1 ) OP rhs_( t1 ); } \
  bool operator ()() const { return lhs_() OP rhs_(); } \
}; \
template<class L, class R> inline \
NAME<typename detail::tr<L>::type, typename detail::tr<R>::type> \
operator OP(L lhs, R rhs) \
{ \
  typedef typename detail::tr<L>::type lhs_type; \
  typedef typename detail::tr<R>::type rhs_type; \
  return NAME<lhs_type, rhs_type>( lhs_type( lhs ), rhs_type( rhs ) ); \
}

BINARY_BOOL_OP( pf_eq,    == )
BINARY_BOOL_OP( pf_neq,   != )
BINARY_BOOL_OP( pf_less,  <  )
BINARY_BOOL_OP( pf_more,  >  )
BINARY_BOOL_OP( pf_lesse, <= )
BINARY_BOOL_OP( pf_moree, >= )
BINARY_BOOL_OP( pf_and,   && )
BINARY_BOOL_OP( pf_or,    || )

#undef BINARY_BOOL_OP

// --------------------------------------------------------------------------------

} //  namespace lambda

// --------------------------------------------------------------------------------
// lambda bind supports from here.
// --------------------------------------------------------------------------------

namespace lambda
{

// --------------------------------------------------------------------------------

namespace detail
{

  // --------------------------------------------------------------------------------
  
#if defined(AM_CAN_NOT_RETURN_VOID)
typedef void const * default_void;
#else
typedef void default_void;
#endif

template<class T> struct void_to_default_void       { typedef T type; };
template<>        struct void_to_default_void<void> { typedef default_void type; };

// --------------------------------------------------------------------------------

template<typename T> struct is_
{
  // --------------------------------------------------------------------------------

  template<typename U> struct _pointer_of_
  {
    static T testee_;
    static int tester_(...);   // false condition
    static char tester_(U *);  // true condition, typename 'T' matches with typename 'U *' or 'U-derived *'

    enum { value = ( sizeof( char ) == sizeof( tester_( testee_ ) ) ) };

  };  // template<typename U> struct _pointer_of_

  // --------------------------------------------------------------------------------

  template<typename U> struct _reference_of_
  {
    static T testee_;
    static int tester_(...);   // false condition
    static char tester_(U &);  // true condition, typename 'T' matches with typename 'U &' or 'U-derived &'

    enum { value = ( sizeof( char ) == sizeof( tester_( testee_ ) ) ) };

  };  // template<typename U> struct _reference_of_

  // --------------------------------------------------------------------------------

}; // template<typename T> struct is_

// --------------------------------------------------------------------------------

template<typename R> struct binder_impl
{

#if defined(AM_CAN_NOT_RETURN_VOID)
  typedef typename detail::void_to_default_void<R>::type result_type;
#else
  typedef R result_type;
#endif

  // --------------------------------------------------------------------------------

  template<typename> struct select_return
  {
    // --------------------------------------------------------------------------------

    template<typename F> inline
      static result_type fn_invoker(F fn) { return fn(); }

    template<typename F, typename P1> inline
      static result_type fn_invoker(F fn, P1 p1) { return fn( p1 ); }

    template<typename F, typename P1, typename P2> inline
      static result_type fn_invoker(F fn, P1 p1, P2 p2) { return fn( p1, p2 ); }

    template<typename F, typename P1, typename P2, typename P3> inline
      static result_type fn_invoker(F fn, P1 p1, P2 p2, P3 p3) { return fn( p1, p2, p3 ); }

    // --------------------------------------------------------------------------------

    struct invoke_on_pointer
    {
      // --------------------------------------------------------------------------------

      template<typename U, typename T> inline
        static result_type invoke(R (U::*mfn)(), T obj) { return ( obj->*mfn )(); }

      template<typename U, typename P1, typename T, typename A1> inline
        static result_type invoke(R (U::*mfn)(P1), T obj, A1 a1) { return ( obj->*mfn )( a1 ); }

      template<typename U, typename P1, typename P2, typename T, typename A1, typename A2> inline
        static result_type invoke(R (U::*mfn)(P1, P2), T obj, A1 a1, A2 a2) { return ( obj->*mfn )( a1, a2 ); }

      template<typename U, typename P1, typename P2, typename P3, typename T, typename A1, typename A2, typename A3> inline
        static result_type invoke(R (U::*mfn)(P1, P2, P3), T obj, A1 a1, A2 a2, A3 a3) { return ( obj->*mfn )( a1, a2, a3 ); }

      // --------------------------------------------------------------------------------

      template<typename U, typename T> inline
        static result_type invoke_const(R (U::*mfn)() const, T obj) { return ( obj->*mfn )(); }

      template<typename U, typename P1, typename T, typename A1> inline
        static result_type invoke_const(R (U::*mfn)(P1) const, T obj, A1 a1) { return ( obj->*mfn )( a1 ); }

      template<typename U, typename P1, typename P2, typename T, typename A1, typename A2> inline
        static result_type invoke_const(R (U::*mfn)(P1, P2) const, T obj, A1 a1, A2 a2) { return ( obj->*mfn )( a1, a2 ); }

      template<typename U, typename P1, typename P2, typename P3, typename T, typename A1, typename A2, typename A3> inline
        static result_type invoke_const(R (U::*mfn)(P1, P2, P3) const, T obj, A1 a1, A2 a2, A3 a3) { return ( obj->*mfn )( a1, a2, a3 ); }

      // --------------------------------------------------------------------------------

    };  // struct invoke_on_pointer

    // --------------------------------------------------------------------------------

    struct invoke_on_object
    {
      template<typename U, typename T> inline
        static result_type invoke(R (U::*mfn)(), T obj) { return ( static_cast<U &>(obj).*mfn )(); }

      template<typename U, typename P1, typename T, typename A1> inline
        static result_type invoke(R (U::*mfn)(P1), T obj, A1 a1) { return ( static_cast<U &>(obj).*mfn )( a1 ); }

      template<typename U, typename P1, typename P2, typename T, typename A1, typename A2> inline
        static result_type invoke(R (U::*mfn)(P1, P2), T obj, A1 a1, A2 a2) { return ( static_cast<U &>(obj).*mfn )( a1, a2 ); }

      template<typename U, typename P1, typename P2, typename P3, typename T, typename A1, typename A2, typename A3> inline
        static result_type invoke(R (U::*mfn)(P1, P2, P3), T obj, A1 a1, A2 a2, A3 a3) { return ( static_cast<U &>(obj).*mfn )( a1, a2, a3 ); }

      // --------------------------------------------------------------------------------

      template<typename U, typename T> inline
        static result_type invoke_const(R (U::*mfn)() const, T obj) { return ( static_cast<U const &>(obj).*mfn )(); }

      template<typename U, typename P1, typename T, typename A1> inline
        static result_type invoke_const(R (U::*mfn)(P1) const, T obj, A1 a1) { return ( static_cast<U const &>(obj).*mfn )( a1 ); }

      template<typename U, typename P1, typename P2, typename T, typename A1, typename A2> inline
        static result_type invoke_const(R (U::*mfn)(P1, P2) const, T obj, A1 a1, A2 a2) { return ( static_cast<U const &>(obj).*mfn )( a1, a2 ); }

      template<typename U, typename P1, typename P2, typename P3, typename T, typename A1, typename A2, typename A3> inline
        static result_type invoke_const(R (U::*mfn)(P1, P2, P3) const, T obj, A1 a1, A2 a2, A3 a3) { return ( static_cast<U const &>(obj).*mfn )( a1, a2, a3 ); }

      // --------------------------------------------------------------------------------

    };  // struct invoke_on_object

    // --------------------------------------------------------------------------------

  };  // template<typename> struct select_return

// --------------------------------------------------------------------------------
#if defined(AM_CAN_NOT_RETURN_VOID)
// --------------------------------------------------------------------------------

  /*!
   *  @internal  Specialization for the compiler which can not return void.
   */
  template<> struct select_return<void const *>
  {

    // --------------------------------------------------------------------------------

    template<typename F> inline
      static result_type fn_invoker(F fn) { fn(); return 0; }

    template<typename F, typename P1> inline
      static result_type fn_invoker(F fn, P1 p1) { fn( p1 ); return 0; }

    template<typename F, typename P1, typename P2> inline
      static result_type fn_invoker(F fn, P1 p1, P2 p2) { fn( p1, p2 ); return 0; }

    template<typename F, typename P1, typename P2, typename P3> inline
      static result_type fn_invoker(F fn, P1 p1, P2 p2, P3 p3) { fn( p1, p2, p3 ); return 0; }

    // --------------------------------------------------------------------------------

    struct invoke_on_pointer
    {

      // --------------------------------------------------------------------------------

      template<typename U, typename T> inline
        static result_type invoke(R (U::*mfn)(), T obj) { ( obj->*mfn )(); return 0; }

      template<typename U, typename P1, typename T, typename A1> inline
        static result_type invoke(R (U::*mfn)(P1), T obj, A1 a1) { ( obj->*mfn )( a1 ); return 0; }

      template<typename U, typename P1, typename P2, typename T, typename A1, typename A2> inline
        static result_type invoke(R (U::*mfn)(P1, P2), T obj, A1 a1, A2 a2) { ( obj->*mfn )( a1, a2 ); return 0; }

      template<typename U, typename P1, typename P2, typename P3, typename T, typename A1, typename A2, typename A3> inline
        static result_type invoke(R (U::*mfn)(P1, P2, P3), T obj, A1 a1, A2 a2, A3 a3) { ( obj->*mfn )( a1, a2, a3 ); return 0; }

      // --------------------------------------------------------------------------------

      template<typename U, typename T> inline
        static result_type invoke_const(R (U::*mfn)() const, T obj) { ( obj->*mfn )(); return 0; }

      template<typename U, typename P1, typename T, typename A1> inline
        static result_type invoke_const(R (U::*mfn)(P1) const, T obj, A1 a1) { ( obj->*mfn )( a1 ); return 0; }

      template<typename U, typename P1, typename P2, typename T, typename A1, typename A2> inline
        static result_type invoke_const(R (U::*mfn)(P1, P2) const, T obj, A1 a1, A2 a2) { ( obj->*mfn )( a1, a2 ); return 0; }

      template<typename U, typename P1, typename P2, typename P3, typename T, typename A1, typename A2, typename A3> inline
        static result_type invoke_const(R (U::*mfn)(P1, P2, P3) const, T obj, A1 a1, A2 a2, A3 a3) { ( obj->*mfn )( a1, a2, a3 ); return 0; }

      // --------------------------------------------------------------------------------

    };  // struct invoke_on_pointer

    // --------------------------------------------------------------------------------

    struct invoke_on_object
    {
      template<typename U, typename T> inline
        static result_type invoke(R (U::*mfn)(), T obj) { ( static_cast<U &>(obj).*mfn )(); return 0; }

      template<typename U, typename P1, typename T, typename A1> inline
        static result_type invoke(R (U::*mfn)(P1), T obj, A1 a1) { ( static_cast<U &>(obj).*mfn )( a1 ); return 0; }

      template<typename U, typename P1, typename P2, typename T, typename A1, typename A2> inline
        static result_type invoke(R (U::*mfn)(P1, P2), T obj, A1 a1, A2 a2) { ( static_cast<U &>(obj).*mfn )( a1, a2 ); return 0; }

      template<typename U, typename P1, typename P2, typename P3, typename T, typename A1, typename A2, typename A3> inline
        static result_type invoke(R (U::*mfn)(P1, P2, P3), T obj, A1 a1, A2 a2, A3 a3) { ( static_cast<U &>(obj).*mfn )( a1, a2, a3 ); return 0; }

      // --------------------------------------------------------------------------------

      template<typename U, typename T> inline
        static result_type invoke_const(R (U::*mfn)() const, T obj) { ( static_cast<U const &>(obj).*mfn )(); return 0; }

      template<typename U, typename P1, typename T, typename A1> inline
        static result_type invoke_const(R (U::*mfn)(P1) const, T obj, A1 a1) { ( static_cast<U const &>(obj).*mfn )( a1 ); return 0; }

      template<typename U, typename P1, typename P2, typename T, typename A1, typename A2> inline
        static result_type invoke_const(R (U::*mfn)(P1, P2) const, T obj, A1 a1, A2 a2) { ( static_cast<U const &>(obj).*mfn )( a1, a2 ); return 0; }

      template<typename U, typename P1, typename P2, typename P3, typename T, typename A1, typename A2, typename A3> inline
        static result_type invoke_const(R (U::*mfn)(P1, P2, P3) const, T obj, A1 a1, A2 a2, A3 a3) { ( static_cast<U const &>(obj).*mfn )( a1, a2, a3 ); return 0; }

    };  // struct invoke_on_object

    // --------------------------------------------------------------------------------

  };  // template<> struct select_return<void const *>

// --------------------------------------------------------------------------------
#endif  // #if defined(AM_CAN_NOT_RETURN_VOID)
// --------------------------------------------------------------------------------

  template<typename U, typename T> inline
    static result_type mfn_invoker(R (U::*mfn)(), T obj)
  {
    enum { is_pointer = is_<T>::template _pointer_of_<U>::value };
    typedef typename select_return<result_type>::invoke_on_pointer on_pointer;
    typedef typename select_return<result_type>::invoke_on_object on_object;

    typedef typename detail::if_<is_pointer, on_pointer, on_object>::type select_mfn_invoker;

    return select_mfn_invoker::invoke( mfn, obj );
  }

  template<typename U, typename P1, typename T, typename A1> inline
    static result_type mfn_invoker(R (U::*mfn)(P1), T obj, A1 a1)
  {
    enum { is_pointer = is_<T>::template _pointer_of_<U>::value };
    typedef typename select_return<result_type>::invoke_on_pointer on_pointer;
    typedef typename select_return<result_type>::invoke_on_object on_object;

    typedef typename detail::if_<is_pointer, on_pointer, on_object>::type select_mfn_invoker;

    return select_mfn_invoker::invoke( mfn, obj, a1 );
  }

  template<typename U, typename P1, typename P2, typename T, typename A1, typename A2> inline
    static result_type mfn_invoker(R (U::*mfn)(P1, P2), T obj, A1 a1, A2 a2)
  {
    enum { is_pointer = is_<T>::template _pointer_of_<U>::value };
    typedef typename select_return<result_type>::invoke_on_pointer on_pointer;
    typedef typename select_return<result_type>::invoke_on_object on_object;

    typedef typename detail::if_<is_pointer, on_pointer, on_object>::type select_mfn_invoker;

    return select_mfn_invoker::invoke( mfn, obj, a1, a2 );
  }

  template<typename U, typename P1, typename P2, typename P3, typename T, typename A1, typename A2, typename A3> inline
    static result_type mfn_invoker(R (U::*mfn)(P1, P2, P3), T obj, A1 a1, A2 a2, A3 a3)
  {
    enum { is_pointer = is_<T>::template _pointer_of_<U>::value };
    typedef typename select_return<result_type>::invoke_on_pointer on_pointer;
    typedef typename select_return<result_type>::invoke_on_object on_object;

    typedef typename detail::if_<is_pointer, on_pointer, on_object>::type select_mfn_invoker;

    return select_mfn_invoker::invoke( mfn, obj, a1, a2, a3 );
  }

  // --------------------------------------------------------------------------------

  template<typename U, typename T> inline
    static result_type mfn_const_invoker(R (U::*mfn)() const, T obj)
  {
    enum { is_const_pointer = is_<T>::template _pointer_of_<U const>::value };
    typedef typename select_return<result_type>::invoke_on_pointer on_pointer;
    typedef typename select_return<result_type>::invoke_on_object on_object;

    typedef typename detail::if_<is_const_pointer, on_pointer, on_object>::type select_mfn_invoker;

    return select_mfn_invoker::invoke_const( mfn, obj );
  }

  template<typename U, typename P1, typename T, typename A1> inline
    static result_type mfn_const_invoker(R (U::*mfn)(P1) const, T obj, A1 a1)
  {
    enum { is_const_pointer = is_<T>::template _pointer_of_<U const>::value };
    typedef typename select_return<result_type>::invoke_on_pointer on_pointer;
    typedef typename select_return<result_type>::invoke_on_object on_object;

    typedef typename detail::if_<is_const_pointer, on_pointer, on_object>::type select_mfn_invoker;

    return select_mfn_invoker::invoke_const( mfn, obj, a1 );
  }

  template<typename U, typename P1, typename P2, typename T, typename A1, typename A2> inline
    static result_type mfn_const_invoker(R (U::*mfn)(P1, P2) const, T obj, A1 a1, A2 a2)
  {
    enum { is_const_pointer = is_<T>::template _pointer_of_<U const>::value };
    typedef typename select_return<result_type>::invoke_on_pointer on_pointer;
    typedef typename select_return<result_type>::invoke_on_object on_object;

    typedef typename detail::if_<is_const_pointer, on_pointer, on_object>::type select_mfn_invoker;

    return select_mfn_invoker::invoke_const( mfn, obj, a1, a2 );
  }

  template<typename U, typename P1, typename P2, typename P3, typename T, typename A1, typename A2, typename A3> inline
    static result_type mfn_const_invoker(R (U::*mfn)(P1, P2, P3) const, T obj, A1 a1, A2 a2, A3 a3)
  {
    enum { is_const_pointer = is_<T>::template _pointer_of_<U const>::value };
    typedef typename select_return<result_type>::invoke_on_pointer on_pointer;
    typedef typename select_return<result_type>::invoke_on_object on_object;

    typedef typename detail::if_<is_const_pointer, on_pointer, on_object>::type select_mfn_invoker;

    return select_mfn_invoker::invoke_const( mfn, obj, a1, a2, a3 );
  }

  // --------------------------------------------------------------------------------

};  // template<typename R> struct binder_impl

// --------------------------------------------------------------------------------

} // namespace detail

// --------------------------------------------------------------------------------


/*! Binder for the member function which takes the first argument as object
 *  on which the member function is being called and no extra arugement.
 */
template<typename R, typename U, typename A1> struct binder_obj0 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;
  R (U::*mfn_)(); A1 a1_;

  binder_obj0(R (U::*mfn)(), A1 a1) : mfn_( mfn ), a1_( a1 ) { }
  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_() );
  }

};  // template<typename R, typename U, typename A1> struct binder_obj0

// --------------------------------------------------------------------------------

/*! Bind the member function with the object on which the function call is made.
 *
 *  @param[in] mfn Specifies the member function pointer which takes no input parameter
 *                  and return @a R type
 *  @param[in] a1 Specifies the object on which the function call is made.
 *  @return Function object which calls the specified member function on the specified
 *          bound object.
 *
 *  @sa binder_obj0
 */
template<typename R, typename U, typename A1> inline
binder_obj0<R, U, typename detail::tr<A1>::type>
bind(R (U::*mfn)(), A1 a1)
{
  typedef typename detail::tr<A1>::type TA1;
  return binder_obj0<R, U, TA1>( mfn, TA1( a1 ) );
}

// --------------------------------------------------------------------------------

/*! Binder for the const member function which takes the first argument as object
 *  on which the member function is being called and no extra arugement.
 */
template<typename R, typename U, typename A1> struct binder_const_obj0 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;
  R (U::*mfn_)() const; A1 a1_;

  binder_const_obj0(R (U::*mfn)() const, A1 a1) : mfn_( mfn ), a1_( a1 ) { }
  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_() );
  }

};  // template<typename R, typename U, typename A1> struct binder_const_obj0

// --------------------------------------------------------------------------------

/*! Bind the const member function with the object on which the function call is
 *  made.
 *
 *  @param[in] mfn Specifies the const member function pointer which takes no input
 *                  parameter and return @a R type
 *  @param[in] a1 Specifies the object on which the function call is made.
 *  @return Function object which calls the specified const member function on the
 *          specified bound object.
 *
 *  @sa binder_const_obj0
 */
template<typename R, typename U, typename A1> inline
binder_const_obj0<R, U, typename detail::tr<A1>::type>
bind(R (U::*mfn)() const, A1 a1)
{
  typedef typename detail::tr<A1>::type TA1;
  return binder_const_obj0<R, U, TA1>( mfn, TA1( a1 ) );
}

// --------------------------------------------------------------------------------

/*! Binder for the member function which takes the first argument as object
 *  on which the member function is being called and one more argument.
 */
template<typename R, typename P1, typename U, typename A1, typename A2> struct binder_obj1 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;
  R (U::*mfn_)(P1); A1 a1_; A2 a2_;

  binder_obj1(R (U::*mfn)(P1), A1 a1, A2 a2) : mfn_( mfn ), a1_( a1 ), a2_( a2 ) { }
  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1, t2, t3 ), a2_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1, t2 ), a2_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1 ), a2_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_(), a2_() );
  }

};  // template<typename R, typename P1, typename U, typename A1, typename A2> struct binder_obj1

// --------------------------------------------------------------------------------

/*! Bind the member function with the object on which the function call is made and
 *  with a specified input argument.
 *
 *  @param[in] mfn Specifies the member function pointer which takes an input parameter
 *                  and return @a R type
 *  @param[in] a1 Specifies the object on which the function call is made.
 *  @param[in] a2 Specifies the first input augment.
 *  @return Function object which calls the specified member function on the specified
 *          bound object with the specified input argument.
 *
 *  @sa binder_obj1
 */
template<typename R, typename P1, typename U, typename A1, typename A2> inline
binder_obj1<R, P1, U, typename detail::tr<A1>::type, typename detail::tr<A2>::type>
bind(R (U::*mfn)(P1), A1 a1, A2 a2)
{
  typedef typename detail::tr<A1>::type TA1;
  typedef typename detail::tr<A2>::type TA2;
  return binder_obj1<R, P1, U, TA1, TA2>( mfn, TA1( a1 ), TA2( a2 ) );
}

// --------------------------------------------------------------------------------

/*! Binder for the const member function which takes the first argument as object
 *  on which the member function is being called and one more argument.
 */
template<typename R, typename P1, typename U, typename A1, typename A2> struct binder_const_obj1 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;
  R (U::*mfn_)(P1) const; A1 a1_; A2 a2_;

  binder_const_obj1(R (U::*mfn)(P1) const, A1 a1, A2 a2) : mfn_( mfn ), a1_( a1 ), a2_( a2 ) { }
  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1, t2, t3 ), a2_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1, t2 ), a2_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1 ), a2_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_(), a2_() );
  }

};  // template<typename R, typename P1, typename U, typename A1, typename A2> struct binder_const_obj1

// --------------------------------------------------------------------------------

/*! Bind the const member function with the object on which the function call is
 *  made and with a specified input argument.
 *
 *  @param[in] mfn Specifies the const member function pointer which takes an input
 *                  parameter and return @a R type
 *  @param[in] a1 Specifies the object on which the function call is made.
 *  @param[in] a2 Specifies the first input augment.
 *  @return Function object which calls the specified const member function on the
 *          specified bound object with the specified input argument.
 *
 *  @sa binder_const_obj1
 */
template<typename R, typename P1, typename U, typename A1, typename A2> inline
binder_const_obj1<R, P1, U, typename detail::tr<A1>::type, typename detail::tr<A2>::type>
bind(R (U::*mfn)(P1) const, A1 a1, A2 a2)
{
  typedef typename detail::tr<A1>::type TA1;
  typedef typename detail::tr<A2>::type TA2;
  return binder_const_obj1<R, P1, U, TA1, TA2>( mfn, TA1( a1 ), TA2( a2 ) );
}

// --------------------------------------------------------------------------------

/*! Binder for the member function which takes the first argument as object
 *  on which the member function is being called and two more arguments.
 */
template<typename R, typename P1, typename P2, typename U, typename A1, typename A2, typename A3> struct binder_obj2 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;
  R (U::*mfn_)(P1, P2); A1 a1_; A2 a2_; A3 a3_;

  binder_obj2(R (U::*mfn)(P1, P2), A1 a1, A2 a2, A3 a3) : mfn_( mfn ), a1_( a1 ), a2_( a2 ), a3_( a3 ) { }
  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1, t2, t3 ), a2_( t1, t2, t3 ), a3_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1, t2 ), a2_( t1, t2 ), a3_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1 ), a2_( t1 ), a3_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_(), a2_(), a3_() );
  }

};  // template<typename R, typename P1, typename P2, typename U, typename A1, typename A2, typename A3> struct binder_obj2

// --------------------------------------------------------------------------------

/*! Bind the member function with the object on which the function call is made and
 *  with two specified input arguments.
 *
 *  @param[in] mfn Specifies the member function pointer which takes two input
 *                  arguments and return @a R type
 *  @param[in] a1 Specifies the object on which the function call is made.
 *  @param[in] a2 Specifies the first input augment.
 *  @param[in] a3 Specifies the second input augment.
 *  @return Function object which calls the specified member function on the specified
 *          bound object with the specified input arguments.
 *
 *  @sa binder_obj2
 */
template<typename R, typename P1, typename P2, typename U, typename A1, typename A2, typename A3> inline
binder_obj2<R, P1, P2, U, typename detail::tr<A1>::type, typename detail::tr<A2>::type, typename detail::tr<A3>::type>
bind(R (U::*mfn)(P1, P2), A1 a1, A2 a2, A3 a3)
{
  typedef typename detail::tr<A1>::type TA1;
  typedef typename detail::tr<A2>::type TA2;
  typedef typename detail::tr<A3>::type TA3;
  return binder_obj2<R, P1, P2, U, TA1, TA2, TA3>( mfn, TA1( a1 ), TA2( a2 ), TA3( a3 ) );
}

// --------------------------------------------------------------------------------

/*! Binder for the const member function which takes the first argument as object
 *  on which the member function is being called and two more arguments.
 */
template<typename R, typename P1, typename P2, typename U, typename A1, typename A2, typename A3> struct binder_const_obj2 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;
  R (U::*mfn_)(P1, P2) const; A1 a1_; A2 a2_; A3 a3_;

  binder_const_obj2(R (U::*mfn)(P1, P2) const, A1 a1, A2 a2, A3 a3) : mfn_( mfn ), a1_( a1 ), a2_( a2 ), a3_( a3 ) { }
  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1, t2, t3 ), a2_( t1, t2, t3 ), a3_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1, t2 ), a2_( t1, t2 ), a3_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1 ), a2_( t1 ), a3_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_(), a2_(), a3_() );
  }

};  // template<typename R, typename P1, typename P2, typename U, typename A1, typename A2, typename A3> struct binder_const_obj2

// --------------------------------------------------------------------------------

/*! Bind the const member function with the object on which the function call is
 *  made and with two specified input arguments.
 *
 *  @param[in] mfn Specifies the const member function pointer which takes two input
 *                  arguments and return @a R type
 *  @param[in] a1 Specifies the object on which the function call is made.
 *  @param[in] a2 Specifies the first input augment.
 *  @param[in] a3 Specifies the second input augment.
 *  @return Function object which calls the specified const member function on the
 *          specified bound object with the specified input arguments.
 *
 *  @sa binder_const_obj2
 */
template<typename R, typename P1, typename P2, typename U, typename A1, typename A2, typename A3> inline
binder_const_obj2<R, P1, P2, U, typename detail::tr<A1>::type, typename detail::tr<A2>::type, typename detail::tr<A3>::type>
bind(R (U::*mfn)(P1, P2) const, A1 a1, A2 a2, A3 a3)
{
  typedef typename detail::tr<A1>::type TA1;
  typedef typename detail::tr<A2>::type TA2;
  typedef typename detail::tr<A3>::type TA3;
  return binder_const_obj2<R, P1, P2, U, TA1, TA2, TA3>( mfn, TA1( a1 ), TA2( a2 ), TA3( a3 ) );
}

// --------------------------------------------------------------------------------

/*! Binder for the member function which takes the first argument as object
 *  on which the member function is being called and three more arguments.
 */
template<typename R, typename P1, typename P2, typename P3, typename U, typename A1, typename A2, typename A3, typename A4> struct binder_obj3 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;
  R (U::*mfn_)(P1, P2, P3); A1 a1_; A2 a2_; A3 a3_; A4 a4_;

  binder_obj3(R (U::*mfn)(P1, P2, P3), A1 a1, A2 a2, A3 a3, A4 a4) : mfn_( mfn ), a1_( a1 ), a2_( a2 ), a3_( a3 ), a4_( a4 ) { }
  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1, t2, t3 ), a2_( t1, t2, t3 ), a3_( t1, t2, t3 ), a4_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1, t2 ), a2_( t1, t2 ), a3_( t1, t2 ), a4_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_( t1 ), a2_( t1 ), a3_( t1 ), a4_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::mfn_invoker( mfn_, a1_(), a2_(), a3_(), a4_() );
  }

};  // template<typename R, typename P1, typename P2, typename P3, typename U, typename A1, typename A2, typename A3, typename A4> struct binder_obj3

// --------------------------------------------------------------------------------

/*! Bind the member function with the object on which the function call is made and
 *  with three specified input arguments.
 *
 *  @param[in] mfn Specifies the member function pointer which takes three input
 *                  arguments and return @a R type
 *  @param[in] a1 Specifies the object on which the function call is made.
 *  @param[in] a2 Specifies the first input augment.
 *  @param[in] a3 Specifies the second input augment.
 *  @param[in] a4 Specifies the third input augment.
 *  @return Function object which calls the specified member function on the specified
 *          bound object with the specified input arguments.
 *
 *  @sa binder_obj3
 */
template<typename R, typename P1, typename P2, typename P3, typename U, typename A1, typename A2, typename A3, typename A4> inline
binder_obj3<R, P1, P2, P3, U, typename detail::tr<A1>::type, typename detail::tr<A2>::type, typename detail::tr<A3>::type, typename detail::tr<A4>::type>
bind(R (U::*mfn)(P1, P2, P3), A1 a1, A2 a2, A3 a3, A4 a4)
{
  typedef typename detail::tr<A1>::type TA1;
  typedef typename detail::tr<A2>::type TA2;
  typedef typename detail::tr<A3>::type TA3;
  typedef typename detail::tr<A4>::type TA4;
  return binder_obj3<R, P1, P2, P3, U, TA1, TA2, TA3, TA4>( mfn, TA1( a1 ), TA2( a2 ), TA3( a3 ), TA4( a4 ) );
}

// --------------------------------------------------------------------------------

/*! Binder for the const member function which takes the first argument as object
 *  on which the member function is being called and three more arguments.
 */
template<typename R, typename P1, typename P2, typename P3, typename U, typename A1, typename A2, typename A3, typename A4> struct binder_const_obj3 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;
  R (U::*mfn_)(P1, P2, P3) const; A1 a1_; A2 a2_; A3 a3_; A4 a4_;

  binder_const_obj3(R (U::*mfn)(P1, P2, P3) const, A1 a1, A2 a2, A3 a3, A4 a4) : mfn_( mfn ), a1_( a1 ), a2_( a2 ), a3_( a3 ), a4_( a4 ) { }
  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1, t2 ), a2_( t1, t2, t3 ), a3_( t1, t2, t3 ), a4_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1, t2 ), a2_( t1, t2 ), a3_( t1, t2 ), a4_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_( t1 ), a2_( t1 ), a3_( t1 ), a4_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::mfn_const_invoker( mfn_, a1_(), a2_(), a3_(), a4_() );
  }

};  // template<typename R, typename P1, typename P2, typename P3, typename U, typename A1, typename A2, typename A3, typename A4> struct binder_const_obj3

// --------------------------------------------------------------------------------

/*! Bind the const member function with the object on which the function call is
 *  made and with three specified input arguments.
 *
 *  @param[in] mfn Specifies the const member function pointer which takes three
 *                  input arguments and return @a R type
 *  @param[in] a1 Specifies the object on which the function call is made.
 *  @param[in] a2 Specifies the first input augment.
 *  @param[in] a3 Specifies the second input augment.
 *  @param[in] a4 Specifies the third input augment.
 *  @return Function object which calls the specified const member function on the
 *          specified bound object with the specified input arguments.
 *
 *  @sa binder_const_obj3
 */
template<typename R, typename P1, typename P2, typename P3, typename U, typename A1, typename A2, typename A3, typename A4> inline
binder_const_obj3<R, P1, P2, P3, U, typename detail::tr<A1>::type, typename detail::tr<A2>::type, typename detail::tr<A3>::type, typename detail::tr<A4>::type>
bind(R (U::*mfn)(P1, P2, P3) const, A1 a1, A2 a2, A3 a3, A4 a4)
{
  typedef typename detail::tr<A1>::type TA1;
  typedef typename detail::tr<A2>::type TA2;
  typedef typename detail::tr<A3>::type TA3;
  typedef typename detail::tr<A4>::type TA4;
  return binder_const_obj3<R, P1, P2, P3, U, TA1, TA2, TA3, TA4>( mfn, TA1( a1 ), TA2( a2 ), TA3( a3 ), TA4( a4 ) );
}

// --------------------------------------------------------------------------------

/*! Binder for the free function which takes no argument.
 */
template<typename R> struct binder0 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;

  R (* fn_)();
  binder0(R (* fn)()) : fn_( fn ) { }

  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_ );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_ );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_ );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_ );
  }

};  // template<typename R> struct binder0

// --------------------------------------------------------------------------------

/*! Bind the free function with no input argument.
 *
 *  @param[in] fn Specifies the free function pointer which takes no input argument
 *                and return @a R type
 *  @return Function object which calls the specified free function.
 *
 *  @sa binder0
 */
template<typename R> inline
binder0<R>
bind(R (* fn)())
{
  return binder0<R>( fn );
}

// --------------------------------------------------------------------------------

/*! Binder for the free function which takes one argument.
 */
template<typename R, typename P1, typename A1> struct binder1 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;

  R (* fn_)(P1); A1 a1_;
  binder1(R (* fn)(P1), A1 a1) : fn_( fn ), a1_( a1 ) { }

  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_() );
  }

};  // template<typename R, typename P1, typename A1> struct binder1

// --------------------------------------------------------------------------------

/*! Bind the free function with a specified input argument.
 *
 *  @param[in] fn Specifies the free function pointer which takes an input argument
 *                and return @a R type
 *  @param[in] a1 Specifies the first input augment.
 *  @return Function object which calls the specified free function with the
 *          specified input argument.
 *
 *  @sa binder1
 */
template<typename R, typename P1, typename A1> inline
binder1<R, P1, typename detail::tr<A1>::type >
bind(R (* fn)(P1), A1 a1)
{
  typedef typename detail::tr<A1>::type TA1;
  return binder1<R, P1, TA1>( fn, TA1( a1 ) );
}

// --------------------------------------------------------------------------------

/*! Binder for the free function which takes two arguments.
 */
template<typename R, typename P1, typename P2, typename A1, typename A2> struct binder2 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;

  R (* fn_)(P1, P2); A1 a1_; A2 a2_;
  binder2(R (* fn)(P1, P2), A1 a1, A2 a2) : fn_( fn ), a1_( a1 ), a2_( a2 ) { }

  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2, t3 ), a2_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2 ), a2_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1 ), a2_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_(), a2_() );
  }

};  // template<typename R, typename P1, typename A1, typename A2> struct binder2

// --------------------------------------------------------------------------------

/*! Bind the free function with two specified input arguments.
 *
 *  @param[in] fn Specifies the free function pointer which takes two input arguments
 *                and return @a R type
 *  @param[in] a1 Specifies the first input augment.
 *  @param[in] a2 Specifies the second input augment.
 *  @return Function object which calls the specified free function with two
 *          specified input arguments.
 *
 *  @sa binder2
 */
template<typename R, typename P1, typename P2, typename A1, typename A2> inline
binder2<R, P1, P2, typename detail::tr<A1>::type, typename detail::tr<A2>::type >
bind(R (* fn)(P1, P2), A1 a1, A2 a2)
{
  typedef typename detail::tr<A1>::type TA1;
  typedef typename detail::tr<A2>::type TA2;
  return binder2<R, P1, P2, TA1, TA2>( fn, TA1( a1 ), TA2( a2 ) );
}

// --------------------------------------------------------------------------------

/*! Binder for the free function which takes three arguments.
 */
template<typename R, typename P1, typename P2, typename P3, typename A1, typename A2, typename A3> struct binder3 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;

  R (* fn_)(P1, P2, P3); A1 a1_; A2 a2_; A3 a3_;
  binder3(R (* fn)(P1, P2, P3), A1 a1, A2 a2, A3 a3) : fn_( fn ), a1_( a1 ), a2_( a2 ), a3_( a3 ) { }

  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2, t3 ), a2_( t1, t2, t3 ), a3_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2 ), a2_( t1, t2 ), a3_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1 ), a2_( t1 ), a3_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_(), a2_(), a3_() );
  }

};  // template<typename R, typename P1, typename P2, typename P3, typename A1, typename A2, typename A3> struct binder3

// --------------------------------------------------------------------------------

/*! Bind the free function with three specified input arguments.
 *
 *  @param[in] fn Specifies the free function pointer which takes three input arguments
 *                and return @a R type
 *  @param[in] a1 Specifies the first input augment.
 *  @param[in] a2 Specifies the second input augment.
 *  @param[in] a3 Specifies the third input augment.
 *  @return Function object which calls the specified free function with three
 *          specified input arguments.
 *
 *  @sa binder3
 */
template<typename R, typename P1, typename P2, typename P3, typename A1, typename A2, typename A3> inline
binder3<R, P1, P2, P3, typename detail::tr<A1>::type, typename detail::tr<A2>::type, typename detail::tr<A3>::type >
bind(R (* fn)(P1, P2, P3), A1 a1, A2 a2, A3 a3)
{
  typedef typename detail::tr<A1>::type TA1;
  typedef typename detail::tr<A2>::type TA2;
  typedef typename detail::tr<A3>::type TA3;
  return binder3<R, P1, P2, P3, TA1, TA2, TA3>( fn, TA1( a1 ), TA2( a2 ), TA3( a3 ) );
}

// --------------------------------------------------------------------------------
#if defined(AM_BIND_ENABLE_STDCALL)
// --------------------------------------------------------------------------------

/*! Binder for the free function which takes no argument.
 */
template<typename R> struct binder_stdcall0 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;

  AM_STDCALL_FN_POINTER0(R, fn_);
  binder_stdcall0(AM_STDCALL_FN_POINTER0(R, fn)) : fn_( fn ) { }

  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_ );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_ );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_ );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_ );
  }

};  // template<typename R> struct binder_stdcall0

// --------------------------------------------------------------------------------

/*! Bind the free function with no input argument.
 *
 *  @param[in] fn Specifies the free function pointer which takes no input argument
 *                and return @a R type
 *  @return Function object which calls the specified free function.
 *
 *  @sa binder0
 */
template<typename R> inline
binder_stdcall0<R>
bind(AM_STDCALL_FN_POINTER0(R, fn), int d = 0)
{
  return binder_stdcall0<R>( fn );
}

// --------------------------------------------------------------------------------

template<typename R, typename P1, typename A1> struct binder_stdcall1 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;

  AM_STDCALL_FN_POINTER1(R, fn_, P1); A1 a1_;
  binder_stdcall1(AM_STDCALL_FN_POINTER1(R, fn, P1), A1 a1) : fn_( fn ), a1_( a1 ) { }

  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_() );
  }

};  // template<typename R, typename P1, typename A1> struct binder_stdcall1

// --------------------------------------------------------------------------------

template<typename R, typename P1, typename A1> inline
binder_stdcall1<R, P1, typename detail::tr<A1>::type >
bind(AM_STDCALL_FN_POINTER1(R, fn, P1), A1 a1, int d = 0)
{
  typedef typename detail::tr<A1>::type TA1;
  return binder_stdcall1<R, P1, TA1>( fn, TA1( a1 ) );
}

// --------------------------------------------------------------------------------

template<typename R, typename P1, typename P2, typename A1, typename A2> struct binder_stdcall2 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;

  AM_STDCALL_FN_POINTER2(R, fn_, P1, P2); A1 a1_; A2 a2_;
  binder_stdcall2(AM_STDCALL_FN_POINTER2(R, fn, P1, P2), A1 a1, A2 a2) : fn_( fn ), a1_( a1 ), a2_( a2 ) { }

  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2, t3 ), a2_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2 ), a2_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1 ), a2_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_(), a2_() );
  }

};  // template<typename R, typename P1, typename A1, typename A2> struct binder_stdcall2

// --------------------------------------------------------------------------------

template<typename R, typename P1, typename P2, typename A1, typename A2> inline
binder_stdcall2<R, P1, P2, typename detail::tr<A1>::type, typename detail::tr<A2>::type >
bind(AM_STDCALL_FN_POINTER2(R, fn, P1, P2), A1 a1, A2 a2, int d = 0)
{
  typedef typename detail::tr<A1>::type TA1;
  typedef typename detail::tr<A2>::type TA2;
  return binder_stdcall2<R, P1, P2, TA1, TA2>( fn, TA1( a1 ), TA2( a2 ) );
}

// --------------------------------------------------------------------------------

template<typename R, typename P1, typename P2, typename P3, typename A1, typename A2, typename A3> struct binder_stdcall3 : public detail::lambda_op_tag
{
  typedef typename detail::binder_impl<R>::result_type result_type;

  AM_STDCALL_FN_POINTER3(R, fn_, P1, P2, P3); A1 a1_; A2 a2_; A3 a3_;
  binder_stdcall3(AM_STDCALL_FN_POINTER3(R, fn, P1, P2, P3), A1 a1, A2 a2, A3 a3) : fn_( fn ), a1_( a1 ), a2_( a2 ), a3_( a3 ) { }

  template<class T1, class T2, class T3> result_type operator ()(T1 t1, T2 t2, T3 t3) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2, t3 ), a2_( t1, t2, t3 ), a3_( t1, t2, t3 ) );
  }
  template<class T1, class T2> result_type operator ()(T1 t1, T2 t2) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1, t2 ), a2_( t1, t2 ), a3_( t1, t2 ) );
  }
  template<class T1> result_type operator ()(T1 t1) const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_( t1 ), a2_( t1 ), a3_( t1 ) );
  }
  result_type operator ()() const
  {
    return detail::binder_impl<R>::template select_return<result_type>::fn_invoker( fn_, a1_(), a2_(), a3_() );
  }

};  // template<typename R, typename P1, typename P2, typename P3, typename A1, typename A2, typename A3> struct binder_stdcall3

// --------------------------------------------------------------------------------

template<typename R, typename P1, typename P2, typename P3, typename A1, typename A2, typename A3> inline
binder_stdcall3<R, P1, P2, P3, typename detail::tr<A1>::type, typename detail::tr<A2>::type, typename detail::tr<A3>::type >
bind(AM_STDCALL_FN_POINTER3(R, fn, P1, P2, P3), A1 a1, A2 a2, A3 a3, int d = 0)
{
  typedef typename detail::tr<A1>::type TA1;
  typedef typename detail::tr<A2>::type TA2;
  typedef typename detail::tr<A3>::type TA3;
  return binder_stdcall3<R, P1, P2, P3, TA1, TA2, TA3>( fn, TA1( a1 ), TA2( a2 ), TA3( a3 ) );
}

// --------------------------------------------------------------------------------
#endif  // #if defined(AM_BIND_ENABLE_STDCALL)
// --------------------------------------------------------------------------------

} // namespace lambda

// --------------------------------------------------------------------------------

} // namespace am

#endif  // #if !defined(__LAMBDA_HPP__INCLUDED__)
