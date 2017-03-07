/**
 * apr tutorial sample code
 * http://dev.ariel-networks.com/apr/
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <apr_general.h>
#include <apr_ring.h>

#include <stdio.h>
#include <apr_ring.h>
#include <apr_strings.h>

/* Your own type.
 * The object becomes an element of a ring container.
 * @remark I prepend an underscore to the structure name.
 *         That's because I want to distinguish it with typedef name as a sample.
 *         It's OK to omit the underscore. */
typedef struct _my_elem_t {
    /* 'link' is just a name of member variable, as which you can choose any name.
     * But, you have to care of its name in the following code like a type name.
     * This seems weird, but don't care so much. */
    APR_RING_ENTRY(_my_elem_t) link;

    /* various values depending on your program */
    int num;
    const char *str;
} my_elem_t;

/* Ring container type */
typedef struct _my_ring_t my_ring_t;
APR_RING_HEAD(_my_ring_t, _my_elem_t);


/**
 * Create a my_elem_t object.
 */
static my_elem_t* create_elem(int i, const char *s, apr_pool_t *mp)
{
    my_elem_t *elem = apr_palloc(mp, sizeof(my_elem_t));
    elem->num = i;
    elem->str = apr_pstrdup(mp, s);
    return elem;
}

static void append_elems_to_ring(my_ring_t *ring, apr_pool_t *mp)
{
    int i;
    for (i = 0; i < 4; i++) {
        my_elem_t *obj = create_elem(i * 10, apr_psprintf(mp, "foo_%d", i), mp);/* XXX 10 is just a magic number for example */
        APR_RING_INSERT_TAIL(ring, obj, _my_elem_t, link);
    }
}

/** @remark ring is sorted by my_elem_t::num */
static void insert_elems_to_ring(my_ring_t *ring, apr_pool_t *mp)
{
    int i;
    for (i = 0; i < 4; i++) {
        my_elem_t *obj = create_elem(i * 12, apr_psprintf(mp, "bar_%d", i), mp);/* XXX 12 is just a magic number for example */
        my_elem_t *ep;
	for (ep = APR_RING_FIRST(ring); ep != APR_RING_SENTINEL(ring, _my_elem_t, link); ep = APR_RING_NEXT(ep, link)) {
            if (ep->num > obj->num) {
                APR_RING_INSERT_BEFORE(ep, obj, link);
                break;
            }
        }
        if (ep == APR_RING_SENTINEL(ring, _my_elem_t, link)) {
            APR_RING_INSERT_TAIL(ring, obj, _my_elem_t, link);
        }
    }
}

static void remove_elems_from_ring(my_ring_t *ring, apr_pool_t *mp)
{
    my_elem_t *ep;
    for (ep = APR_RING_FIRST(ring); ep != APR_RING_SENTINEL(ring, _my_elem_t, link); ep = APR_RING_NEXT(ep, link)) {
        if (ep->num == 20) {/* XXX 20 is just a magic number for example */
            APR_RING_UNSPLICE(ep, ep, link);
        }
    }
}

static void iterate_ring(const my_ring_t *ring)
{
    const my_elem_t *ep;

    puts("iterate_ring");
    for (ep = APR_RING_FIRST(ring); ep != APR_RING_SENTINEL(ring, _my_elem_t, link); ep = APR_RING_NEXT(ep, link)) {
        printf("elem: num=%d, str=%s\n", ep->num, ep->str);
    }
}

static void iterate_reverse_ring(const my_ring_t *ring)
{
    const my_elem_t *ep;

    puts("iterate_reverse_ring");
    for (ep = APR_RING_LAST(ring); ep != APR_RING_SENTINEL(ring, _my_elem_t, link); ep = APR_RING_PREV(ep, link)) {
        printf("elem: num=%d, str=%s\n", ep->num, ep->str);
    }
}

/** @remark ring is not just a doubly linked list, but it's also cyclic */
static const my_elem_t* iterate_loop_ring(const my_ring_t *ring, const my_elem_t *begin)
{
    int i;
    const my_elem_t *ep = begin;

    puts("iterate_loop_ring");
    for (i = 0; i < 4; i++) {
        printf("elem-in-loop: num=%d, str=%s\n", ep->num, ep->str);
        ep = APR_RING_NEXT(ep, link);
        if (ep == APR_RING_SENTINEL(ring, _my_elem_t, link)) {
            ep = APR_RING_NEXT(ep, link);
        }
    }
    return ep;
}

/**
 * apr_ring sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_pool_t *mp;
    my_ring_t *ring;
    const my_elem_t *ep;
	
    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* intialize the ring container */
    ring = apr_palloc(mp, sizeof(my_ring_t));
    APR_RING_INIT(ring, _my_elem_t, link);

    append_elems_to_ring(ring, mp);
    insert_elems_to_ring(ring, mp);
    remove_elems_from_ring(ring, mp);

    iterate_ring(ring);
    iterate_reverse_ring(ring);

    ep = iterate_loop_ring(ring, APR_RING_FIRST(ring));
    ep = iterate_loop_ring(ring, ep);
    iterate_loop_ring(ring, ep);

    apr_terminate();
    return 0;
}
