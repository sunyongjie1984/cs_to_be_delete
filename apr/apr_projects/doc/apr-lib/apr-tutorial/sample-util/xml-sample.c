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
#include <apr_file_io.h>
#include <apr_xml.h>

static apr_status_t make_xml_doc(apr_xml_doc **doc, const char *fname, apr_pool_t *mp);
static apr_status_t traverse_xml_tree(const apr_xml_elem *root, apr_pool_t *mp);

/**
 * apr-xml sample code
 * @remark Error checks omitted
 */
int main(int argc, const char *argv[])
{
    apr_status_t rv;
    apr_pool_t *mp;
    apr_xml_doc *doc;
    apr_xml_elem *root;
    const char *fname;
        
    if (argc < 2) {
        printf("usage %s input-xml-filename\n", argv[0]);
        return 0;
    }
    fname = argv[1];

    apr_initialize();
    apr_pool_create(&mp, NULL);

    /* This is similar to creating an XML DOM tree, although apr_xml_doc is not a DOM */
    rv = make_xml_doc(&doc, fname, mp);
    if (rv != APR_SUCCESS) {
        return -1;
    }

    root = doc->root;
    printf("root-element; name = %s, text = %s\n", root->name, root->first_cdata.first->text);
    traverse_xml_tree(root, mp);

    apr_terminate();
    return 0;
}

static apr_status_t make_xml_doc(apr_xml_doc **doc, const char *fname, apr_pool_t *mp)
{
    apr_xml_parser *parser = apr_xml_parser_create(mp);
    apr_status_t rv;
    apr_file_t *fp;
    
    rv = apr_file_open(&fp, fname, APR_READ|APR_BINARY, 0, mp);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    while (1) {
#define BUFSIZE		1024
        char buf[BUFSIZE];
        apr_size_t len = sizeof(buf);

        rv = apr_file_read(fp, buf, &len);
        if (rv == APR_SUCCESS && len) {
            apr_status_t rv2 = apr_xml_parser_feed(parser, buf, len);
            if (rv2 != APR_SUCCESS) {
                char err[128];
                apr_xml_parser_geterror(parser, err, sizeof(err));
                printf("rv2 = %s\n", err);
                return rv2;
            }
        } else {
            break;
        }
    }
    apr_file_close(fp);

    apr_xml_parser_done(parser, doc);

    return APR_SUCCESS;
}

static apr_status_t traverse_xml_tree(const apr_xml_elem *root, apr_pool_t *mp)
{
    const apr_xml_elem *elem;
    
    for (elem = root->first_child; elem; elem = elem->next) {
        const apr_xml_attr *attr;

        printf("name = %s, text = %s\n", elem->name, elem->first_cdata.first->text);
        printf("following_cdata = %s\n", elem->following_cdata.first->text);
        if (elem->first_child) {
            const apr_xml_elem *fel = elem->first_child;
            const apr_xml_elem *lel = elem->last_child;
            
            printf("first_child:name=%s,text=%s\n", fel->name, fel->first_cdata.first->text);
            printf("last_child:name=%s,text=%s\n", lel->name, lel->first_cdata.first->text);
        }
        for (attr = elem->attr; attr; attr = attr->next) {
            printf("attr: name = %s, text = %s\n", attr->name, attr->value);
        }
    }
    
    return APR_SUCCESS;
}
