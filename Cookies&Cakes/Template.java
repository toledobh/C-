import java.util.Map;
import java.util.HashMap;
import java.util.concurrent.atomic.AtomicInteger;

// Enum for dessert names
enum DessertName {
    COOKIE,
    CAKE
}

// Enum for ingredient names
enum IngredientName {
    FLOUR,
    BUTTER,
    SUGAR,
    EGG,
    VANILLA_EXTRACT,
    BAKING_POWDER,
    CHOCOLATE_CHIPS,
    MILK,
    COCOA_POWDER
}

// Abstract Dessert class
abstract class Dessert {
    private DessertName name;
    private Ingredient ingredient;

    public Dessert(DessertName name, Ingredient ingredient) {
        this.name = name;
        this.ingredient = ingredient;
    }

    public abstract void prepare();

    protected void makeDough() {
        System.out.println("Making dough for " + name);
        // Use ingredient and perform the necessary steps for making the dough
    }

    protected void shape() {
        System.out.println("Shaping " + name);
        // Use ingredient and perform the necessary steps for shaping the dessert
    }

    protected void bake() {
        System.out.println("Baking " + name);
        // Use ingredient and perform the necessary steps for baking the dessert
    }
}

// Cookie class
class Cookie extends Dessert {
    public Cookie(Ingredient ingredient) {
        super(DessertName.COOKIE, ingredient);
    }

    @Override
    public void prepare() {
        makeDough();
        shape();
        bake();
        System.out.println("Cookie preparation completed");
    }
}

// Cake class
class Cake extends Dessert {
    public Cake(Ingredient ingredient) {
        super(DessertName.CAKE, ingredient);
    }

    @Override
    public void prepare() {
        makeDough();
        shape();
        bake();
        System.out.println("Cake preparation completed");
    }
}


// Ingredient class
class Ingredient {
    private IngredientName name;
    private AtomicInteger quantity;

    public Ingredient(IngredientName name, int initialQuantity) {
        this.name = name;
        this.quantity = new AtomicInteger(initialQuantity);
    }

    public IngredientName getName() {
        return name;
    }

    public AtomicInteger getQuantity() {
        return quantity;
    }

    public void stockUp(int amount) {
        quantity.getAndAdd(amount);
        System.out.println("Stocked up " + name + " by " + amount + ", new quantity: " + quantity);
    }
}

// Ingredients class
class Ingredients {
    private Map<IngredientName, Ingredient> stock;

    public Ingredients() {
        stock = new HashMap<>();
        initializeIngredients();
    }

    private void initializeIngredients() {
        stock.put(IngredientName.FLOUR, new Ingredient(IngredientName.FLOUR, 100));
        stock.put(IngredientName.BUTTER, new Ingredient(IngredientName.BUTTER, 50));
        stock.put(IngredientName.SUGAR, new Ingredient(IngredientName.SUGAR, 75));
        stock.put(IngredientName.EGG, new Ingredient(IngredientName.EGG, 20));
    }

    public void stockUp(IngredientName ingredientName, int amount) {
        Ingredient ingredient = stock.get(ingredientName);
        if (ingredient != null) {
            ingredient.stockUp(amount);
        }
    }

    public boolean checkAvailability(IngredientName ingredientName, int amount) {
        Ingredient ingredient = stock.get(ingredientName);
        if (ingredient != null) {
            return ingredient.getQuantity().get() >= amount;
        }
        return false;
    }

    public void consumeIngredients(Map<IngredientName, Integer> ingredients) {
        for (Map.Entry<IngredientName, Integer> entry : ingredients.entrySet()) {
            IngredientName ingredientName = entry.getKey();
            int amount = entry.getValue();

            Ingredient ingredient = stock.get(ingredientName);
            if (ingredient != null) {
                ingredient.getQuantity().getAndAdd(-amount);
            }
        }
    }
}

