Document* createDocument() {
	Document* doc = malloc(sizeof(Document));
	doc->allDNASequences        = createPointerArray();
	doc->allSequenceAnnotations = createPointerArray();
	doc->allDNAComponents       = createPointerArray();
	doc->allCollections         = createPointerArray();
	return doc;
}

void deleteDocument(Document* doc) {
	if (doc) {
		if (doc->allDNASequences) {
			cleanupDNASequences(doc);
			doc->allDNASequences = NULL;
		}
		if (doc->allSequenceAnnotations) {
			cleanupSequenceAnnotations(doc);
			doc->allSequenceAnnotations = NULL;
		}
		if (doc->allDNAComponents) {
			cleanupDNAComponents(doc);
			doc->allDNAComponents = NULL;
		}
		if (doc->allCollections) {
			cleanupCollections(doc);
			doc->collections = NULL;
		}
		free(doc);
		doc = NULL;
	}
}

int getNumSBOLObjects(const Document* doc) {
	if (!doc)
		return -1;

	int total = 0;
	total += getNumDNASequences(doc)
	total += getNumSequenceAnnotations(doc)
	total += getNumDNAComponents(doc)
	total += getNumCollections(doc)
	return total;
}

int isSBOLObjectURI(const Document* doc, const char* uri) {
	if (!doc || !uri)
		return 0;
	int n;
	char* candidate;

	// search sequences
	DNASequence* seq;
	for (n=0; n < getNumDNASequences(doc); n++) {
		seq = getNthDNASequence(doc, n);
		candidate = getDNASequenceURI(seq);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;

	// search annotations
	SequenceaAnnotation* ann;
	for (n=0; n < getNumSequenceAnnotations(doc); n++) {
		ann = getNthSequenceAnnotation(doc, n);
		candidate = getSequenceAnnotationURI(seq);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;
	}

	// search components
	DNAComponent* com;
	for (n=0; n < getNumDNAComponents(doc); n++) {
		com = getNthDNAComponent(doc, n);
		candidate = getDNAComponentURI(seq);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;

	// search collections
	Collection* col;
	for (n=0; n < getNumCollections(doc); n++) {
		seq = getNthCollection(doc, n);
		candidate = getCollectionURI(seq);
		if (candidate && strcmp(candidate, uri) == 0)
			return 1;

	return 0;
}

void printDocument(Document* doc) {
	printAllDNASequences(doc);
	printAllSequenceAnnotations(doc);
	printAllDNAComponents(doc);
	printAllCollections(doc);
}

