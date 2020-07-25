self.addEventListener('install', function(event) {
    event.waitUntil(
        caches.open('SDLchip').then(function(cache) {
            return cache.addAll([
                '/',
                'index.html',
                'SDLchip.js',
                'SDLchip.wasm'
            ]);
        })
    );
});
self.addEventListener('fetch', function(event) {
    event.respondWith(
        caches.match(event.request).then(function(response) {
            return response || fetch(event.request);
        })
    );
});