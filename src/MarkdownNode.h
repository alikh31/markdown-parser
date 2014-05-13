//
//  MarkdownNode.h
//  markdownparser
//
//  Created by Zdenek Nemec on 4/16/14.
//  Copyright (c) 2014 Apiary. All rights reserved.
//

#ifndef MARKDOWNPARSER_NODE_H
#define MARKDOWNPARSER_NODE_H

#include <deque>
#include <memory>
#include "ByteBuffer.h"

namespace mdp {
    
    /** 
     *  AST block node types 
     */
    enum MarkdownNodeType {
        RootMarkdownNodeType = 0,
        CodeMarkdownNodeType,
        QuoteMarkdownNodeType,
        HTMLMarkdownNodeType,
        HeaderMarkdownNodeType,
        HRuleMarkdownNodeType,
        ListItemMarkdownNodeType,
        ParagraphMarkdownNodeType,
        TableMarkdownNodeType,
        TableRowMarkdownNodeType,
        TableCellMarkdownNodeType,
        UndefinedMarkdownNodeType = -1
    };

    /* Forward declaration of AST Node */
    class MarkdownNode;
    
    /** Collection of children nodes */
    typedef std::deque<MarkdownNode> ChildrenNodes;
    
    /** 
     *  AST node
     */
    class MarkdownNode {
    public:
        typedef int Data;
        
        /** Node type */
        MarkdownNodeType type;
        
        /** Textual content, where applicable */
        ByteBuffer text;
        
        /** Additinonal data, if applicable */
        Data data;
        
        /** Source map of the node including any and all children */
        BytesRangeSet sourceMap;
        
        /** Parent node, throws exception if no parent is defined */
        MarkdownNode& parent();
        const MarkdownNode& parent() const;
        
        /** Sets parent node */
        void setParent(MarkdownNode *parent);
        
        /** True if section's parent is specified, false otherwise */
        bool hasParent() const;

        /** Children nodes */
        ChildrenNodes& children();
        const ChildrenNodes& children() const;

        /** Constructor */
        MarkdownNode(MarkdownNodeType type_ = UndefinedMarkdownNodeType,
                MarkdownNode *parent_ = NULL,
                const ByteBuffer& text_ = ByteBuffer(),
                const Data& data_ = Data());

        /** Copy constructor */
        MarkdownNode(const MarkdownNode& rhs);
        
        /** Assignment operator */
        MarkdownNode& operator=(const MarkdownNode& rhs);
        
        /** Destructor */
        ~MarkdownNode();
        
    private:
        MarkdownNode* m_parent;
        std::auto_ptr<ChildrenNodes> m_children;
    };
}

#endif