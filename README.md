Competitive Programming Notes

![](my_snippets/images/algo_topics.jpg)


{% assign doclist = site.pages | sort: 'url'  %}
    {% for doc in doclist %}
         {% if doc.name contains '.md' or doc.name contains '.html' %}
             * <a href="{{ site.baseurl }}{{ doc.url }}">{{ doc.url }}</a>
         {% endif %}
     {% endfor %}


Use dir listing for more topics
https://remidinishanth.github.io/my_USACO/my_snippets/binary_search
