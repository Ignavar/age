#include "postgres.h"

#include "lib/stringinfo.h"
#include "nodes/extensible.h"
#include "nodes/nodes.h"

#include "cypher_nodes.h"

#define DEFINE_AG_NODE(type) \
    type *_node = (type *)node

#define write_node_field(field_name) \
    do \
    { \
        appendStringInfoString(str, " :" CppAsString(field_name) " "); \
        outNode(str, _node->field_name); \
    } while (0)

#define write_string_field(field_name) \
    do \
    { \
        appendStringInfoString(str, " :" CppAsString(field_name) " "); \
        outToken(str, _node->field_name); \
    } while (0)

#define write_bool_field(field_name) \
    do \
    { \
        appendStringInfo(str, " :" CppAsString(field_name) " %s", \
                         _node->field_name ? "true" : "false"); \
    } while (0)

// write an enumerated-type field as an integer code
#define write_enum_field(field_name, enum_type) \
    do \
    { \
        appendStringInfo(str, " :" CppAsString(field_name) " %d", \
                         (int)_node->field_name); \
    } while (0)

/*
 * clauses
 */

void out_cypher_return(StringInfo str, const ExtensibleNode *node)
{
    DEFINE_AG_NODE(cypher_return);

    write_bool_field(distinct);
    write_node_field(items);
    write_node_field(order_by);
    write_node_field(skip);
    write_node_field(limit);
}

void out_cypher_with(StringInfo str, const ExtensibleNode *node)
{
    DEFINE_AG_NODE(cypher_with);

    write_bool_field(distinct);
    write_node_field(items);
    write_node_field(order_by);
    write_node_field(skip);
    write_node_field(limit);
    write_node_field(where);
}

void out_cypher_match(StringInfo str, const ExtensibleNode *node)
{
    DEFINE_AG_NODE(cypher_match);

    write_node_field(pattern);
    write_node_field(where);
}

void out_cypher_create(StringInfo str, const ExtensibleNode *node)
{
    DEFINE_AG_NODE(cypher_create);

    write_node_field(pattern);
}

void out_cypher_set(StringInfo str, const ExtensibleNode *node)
{
    DEFINE_AG_NODE(cypher_set);

    write_node_field(items);
    write_bool_field(is_remove);
}

void out_cypher_set_item(StringInfo str, const ExtensibleNode *node)
{
    DEFINE_AG_NODE(cypher_set_item);

    write_node_field(prop);
    write_node_field(expr);
    write_bool_field(is_add);
}

void out_cypher_delete(StringInfo str, const ExtensibleNode *node)
{
    DEFINE_AG_NODE(cypher_delete);

    write_bool_field(detach);
    write_node_field(exprs);
}

/*
 * pattern
 */

void out_cypher_path(StringInfo str, const ExtensibleNode *node)
{
    DEFINE_AG_NODE(cypher_path);

    write_node_field(path);
}

void out_cypher_node(StringInfo str, const ExtensibleNode *node)
{
    DEFINE_AG_NODE(cypher_node);

    write_string_field(name);
    write_string_field(label);
    write_node_field(props);
}

void out_cypher_relationship(StringInfo str, const ExtensibleNode *node)
{
    DEFINE_AG_NODE(cypher_relationship);

    write_string_field(name);
    write_string_field(label);
    write_node_field(props);
    write_enum_field(dir, cypher_rel_dir);
}