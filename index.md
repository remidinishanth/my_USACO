{% assign doclist = site.pages | sort: 'url'  %}
    {% for doc in doclist %}
         {% if doc.name contains '.md' or doc.name contains '.html' %}
             [href="{{ site.baseurl }}{{ doc.url }}]{{ doc.url }}
         {% endif %}
     {% endfor %}
